#pragma once

#include "ImGui/imgui.h"

#include "../Entity.h"
#include "../GUI/TransformGUI.h"
#include "../GUI/MeshGUI.h"
#include "../GUI/CameraGUI.h"

class EntityGUI
{
private:
	inline void AddTransformComponent(Entity* pEntity, entt::registry& reg)
	{
		if (ImGui::Selectable("Transform"))
		{
			if (reg.any<Transform>(pEntity->entity))
			{
				std::cout << "Entity already has this Component" << std::endl;
			}
			else
			{
				reg.emplace<Transform>(pEntity->entity);
			}
			ImGui::CloseCurrentPopup();
		}
	}

	inline void AddMeshComponent(Entity* pEntity, entt::registry& reg)
	{
		if (ImGui::Selectable("Mesh"))
		{
			if (reg.any<Mesh>(pEntity->entity))
			{
				std::cout << "Entity already has this Component" << std::endl;
			}
			else
			{
				reg.emplace<Mesh>(pEntity->entity);
				if (!reg.any<Transform>(pEntity->entity))
				{
					reg.emplace<Transform>(pEntity->entity);
				}
			}
			ImGui::CloseCurrentPopup();
		}
	}

	inline void AddCameraComponent(Entity* pEntity, entt::registry& reg)
	{
		if (ImGui::Selectable("Camera"))
		{
			if (reg.any<Camera>(pEntity->entity))
			{
				std::cout << "Entity already has this Component" << std::endl;
			}
			else
			{
				reg.emplace<Camera>(pEntity->entity);
				if (!reg.any<Transform>(pEntity->entity))
				{
					reg.emplace<Transform>(pEntity->entity);
				}
			}
		}
	}

	inline void DrawComponentsGUI(Entity* pEntity, entt::registry& reg)
	{
		//TransformGUI
		if (reg.any<Transform>(pEntity->entity))
		{
			auto& transform = reg.get<Transform>(pEntity->entity);
			TransformGUI::DrawGUI(transform);
		}

		//MeshGUI
		if (reg.any<Mesh>(pEntity->entity))
		{
			auto& mesh = reg.get<Mesh>(pEntity->entity);
			MeshGUI::DrawGUI(mesh);
		}

		//Camera GUI
		if (reg.any<Camera>(pEntity->entity))
		{
			auto& camera = reg.get<Camera>(pEntity->entity);
			CameraGUI::DrawGUI(camera);
		}
	}
public:
	void DrawGUI(Entity* pEntity, entt::registry& reg)
	{
		//Base Entity
		ImGui::Begin("Entity");
		ImGui::SetWindowSize(ImVec2(400.0f, 400.0f));

		if (pEntity == nullptr)
		{
			ImGui::Text("No Entity selected");
			return;
		}

		char newName[128] = "";
		strcpy_s(newName, pEntity->name.c_str());
		ImGui::InputText("Name", newName, 128);
		pEntity->name = newName;

		//Add Component Menu
		ImGui::Separator();
		if (ImGui::Button("Add Component"))
		{
			ImGui::OpenPopup("Components");
		}

		if (ImGui::BeginPopup("Components"))
		{
			AddTransformComponent(pEntity, reg);
			AddMeshComponent(pEntity, reg);
			AddCameraComponent(pEntity, reg);
			ImGui::EndPopup();
		}

		//Components
		DrawComponentsGUI(pEntity, reg);

		ImGui::End();
	}
};