#pragma once

#include "ImGui/imgui.h"

#include "../Entity.h"
#include "../GUI/TransformGUI.h"

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

	inline void DrawComponentsGUI(Entity* pEntity, entt::registry& reg)
	{
		//TransformGUI
		if (reg.any<Transform>(pEntity->entity))
		{
			auto& transform = reg.get<Transform>(pEntity->entity);
			TransformGUI::DrawGUI(transform);
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
			ImGui::EndPopup();
		}

		//Components
		DrawComponentsGUI(pEntity, reg);

		ImGui::End();
	}
};