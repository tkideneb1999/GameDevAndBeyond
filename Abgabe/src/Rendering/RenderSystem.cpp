#include "RenderSystem.h"

#include "glm/gtc/matrix_transform.hpp"

#include "Camera.h"

void RenderSystem::RenderSingle(Camera& camera, Transform& transform, Mesh& mesh)
{
	//Enable Object
	glBindVertexArray(mesh.getVAOHandle());
	glBindBuffer(GL_ARRAY_BUFFER, mesh.getVBOHandle());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.getIBOHandle());
	mesh.shader->EnableShader();

	//Set Uniform Data
	glm::mat4 MVP = camera.Projection() * (camera.ViewMatrix(transform) * transform.GetModelMatrix());
	glm::mat4 ITM = glm::transpose(glm::inverse(transform.GetModelMatrix()));

	mesh.shader->SetMatrix4x4("u_MVP", MVP);
	mesh.shader->SetMatrix4x4("u_ITM", ITM);

	//Render
	glDrawElements(GL_TRIANGLES, mesh.getIndicesCount(), GL_UNSIGNED_INT, 0);

	//Cleanup
	mesh.shader->DisableShader();
}

void RenderSystem::Render(entt::registry& registry)
{
	auto cameraView = registry.view<Camera, Transform>();
	
	for (auto cameraEntity : cameraView)
	{
		Camera& camera = cameraView.get<Camera>(cameraEntity);
		Transform& cameraTransform = cameraView.get<Transform>(cameraEntity);
		
		auto meshView = registry.view<Mesh, Transform>();
		
		for (auto meshEntity : meshView)
		{
			Mesh& mesh = meshView.get<Mesh>(meshEntity);
			Transform& meshTransform = meshView.get<Transform>(meshEntity);
			RenderSingle(camera, meshTransform, mesh);
			glm::vec4 color;
			mesh.shader->GetUniform4f("u_Color", color);
			std::cout << "Color: " << color.x << ", " << color.y << ", " << color.z << ", " << color.w << std::endl;
		}
	}
}