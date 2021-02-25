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
			if (reg.any<Transform>(pEntity->entityHandle))
			{
				std::cout << "Entity already has this Component" << std::endl;
			}
			else
			{
				reg.emplace<Transform>(pEntity->entityHandle);
			}
			ImGui::CloseCurrentPopup();
		}
	}

	inline void AddMeshComponent(Entity* pEntity, entt::registry& reg)
	{
		if (ImGui::Selectable("Mesh"))
		{
			if (reg.any<Mesh>(pEntity->entityHandle))
			{
				std::cout << "Entity already has this Component" << std::endl;
			}
			else
			{
				reg.emplace<Mesh>(pEntity->entityHandle);
				if (!reg.any<Transform>(pEntity->entityHandle))
				{
					reg.emplace<Transform>(pEntity->entityHandle);
				}
			}
			ImGui::CloseCurrentPopup();
		}
	}

	inline void AddCameraComponent(Entity* pEntity, entt::registry& reg)
	{
		if (ImGui::Selectable("Camera"))
		{
			if (reg.any<Camera>(pEntity->entityHandle))
			{
				std::cout << "Entity already has this Component" << std::endl;
			}
			else
			{
				reg.emplace<Camera>(pEntity->entityHandle);
				if (!reg.any<Transform>(pEntity->entityHandle))
				{
					reg.emplace<Transform>(pEntity->entityHandle);
				}
			}
		}
	}

	inline void DrawComponentsGUI(Entity* pEntity, entt::registry& reg)
	{
		//TransformGUI
		if (reg.any<Transform>(pEntity->entityHandle))
		{
			auto& transform = reg.get<Transform>(pEntity->entityHandle);
			TransformGUI::DrawGUI(transform);
		}

		//MeshGUI
		if (reg.any<Mesh>(pEntity->entityHandle))
		{
			auto& mesh = reg.get<Mesh>(pEntity->entityHandle);
			MeshGUI::DrawGUI(mesh);
		}

		//Camera GUI
		if (reg.any<Camera>(pEntity->entityHandle))
		{
			auto& camera = reg.get<Camera>(pEntity->entityHandle);
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