#include "RenderSystem.h"

#include "glm/gtc/matrix_transform.hpp"

#include "Camera.h"

void RenderSystem::RenderSingle(Camera& camera, Transform& camtransform, Mesh& mesh, Transform& meshTransform)
{
	//Enable Object
	glBindVertexArray(mesh.getVAOHandle());
	//glBindBuffer(GL_ARRAY_BUFFER, mesh.getVBOHandle());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.getIBOHandle());
	Material& mat = mesh.material;
	mat.GetShader()->EnableShader();

	//Set Uniform Data
	glm::mat4 MVP = camera.Projection() * (camera.ViewMatrix(camtransform) * meshTransform.GetModelMatrix());
	glm::mat4 ITM = glm::transpose(glm::inverse(meshTransform.GetModelMatrix()));

	mat.SetUniform("u_MVP", MVP);

	mat.SetUniform("u_ITM", ITM);
	mat.TansferUniforms();

	//Render
	glDrawElements(GL_TRIANGLES, mesh.getIndicesCount(), GL_UNSIGNED_INT, 0);

	//Cleanup
	mat.GetShader()->DisableShader();
}

void RenderSystem::Render(entt::registry& registry)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
			RenderSingle(camera, cameraTransform, mesh, meshTransform);
		}
	}
}