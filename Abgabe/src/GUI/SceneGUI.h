#pragma once

#include "../Scene.h"
#include "EntityGUI.h"

class SceneGUI
{
private:
	EntityGUI m_entityGUI;
	std::string tempFilePath;
public:
	void DrawGUI(Scene& scene)
	{
		ImGui::SetNextWindowSize(ImVec2(400.0f, 800.0f), ImGuiCond_FirstUseEver);
		ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f), ImGuiCond_FirstUseEver);
		ImGui::SetNextWindowSizeConstraints(ImVec2(100.0f, 300.0f), ImVec2(800.0f, 1000.0f));
		ImGui::Begin("Scene Hierarchy");
		
		

		//Add Entity
		if (ImGui::Button("Add Entity"))
		{
			scene.AddEntity();
		}

		//Save Scene
		ImGui::SameLine();
		if (ImGui::Button("Save Scene"))
		{
			ImGui::OpenPopup("Save Scene?");
		}

		ImVec2 center(ImGui::GetIO().DisplaySize.x * 0.5f, ImGui::GetIO().DisplaySize.y * 0.5f);
		ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
		if (ImGui::BeginPopupModal("Save Scene?", NULL, ImGuiWindowFlags_AlwaysAutoResize))
		{
			char filepath[256] = "";
			strcpy_s(filepath, tempFilePath.c_str());
			ImGui::InputText("Location", filepath, 256);
			tempFilePath = filepath;
			if (ImGui::Button("Save"))
			{
				scene.SerializeScene(tempFilePath.c_str());
				ImGui::CloseCurrentPopup();
				tempFilePath = "";
			}

			ImGui::SameLine();
			if (ImGui::Button("Cancel"))
			{
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}

		//Load Scene
		ImGui::SameLine();
		if (ImGui::Button("Load Scene"))
		{
			ImGui::OpenPopup("Load Scene?");
		}

		if (ImGui::BeginPopupModal("Load Scene?", NULL, ImGuiWindowFlags_AlwaysAutoResize))
		{
			char filepath[256] = "";
			strcpy_s(filepath, tempFilePath.c_str());
			ImGui::InputText("Location", filepath, 256);
			tempFilePath = filepath;
			if (ImGui::Button("Load"))
			{
				scene.DeserializeScene(tempFilePath.c_str());
				ImGui::CloseCurrentPopup();
				tempFilePath = "";
			}

			ImGui::SameLine();
			if (ImGui::Button("Cancel"))
			{
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}

		ImGui::Separator();

		//Entity List
		int markedForDelete = -1;
		ImGui::BeginChild("Entities");
		for (int i = 0; i < scene.m_entityList.size(); i++)
		{
			Entity& currentEntity = scene.m_entityList[i];
			std::string selectableName = currentEntity.name + "##" + std::to_string(i);
			if (ImGui::Selectable(selectableName.c_str()))
			{
				scene.m_activeEntityIndex = i;
			}
			if (ImGui::BeginPopupContextItem())
			{
				std::string contextName = "Context " + currentEntity.name;
				ImGui::Text(contextName.c_str());

				//Delete Entity
				if (ImGui::Selectable("Delete Entity"))
				{
					markedForDelete = i;
					ImGui::CloseCurrentPopup();
				}
				ImGui::EndPopup();
			}
			
		}

		if (markedForDelete != -1)
		{
			scene.RemoveEntity(markedForDelete);
			if (markedForDelete == scene.m_activeEntityIndex)
			{
				scene.m_activeEntityIndex = -1;
			}
			else if (markedForDelete < scene.m_activeEntityIndex)
			{
				scene.m_activeEntityIndex--;
			}
		}
		ImGui::EndChild();
		ImGui::End();

		if (scene.m_activeEntityIndex == -1) return;
		m_entityGUI.DrawGUI(&(scene.m_entityList[scene.m_activeEntityIndex]), scene.m_registry);
	}
};