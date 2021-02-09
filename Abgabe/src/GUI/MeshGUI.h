#pragma once

#include "ImGui/imgui.h"

#include "../Rendering/Mesh.h"

#include "MaterialGUI.h"

class MeshGUI
{
	static std::string typedModelPath;
	static std::string typedMaterialPath;
public:
	static void DrawGUI(Mesh& mesh)
	{
		ImGui::Separator();
		if (ImGui::TreeNode("Mesh"))
		{
			char modelPath[256] = "";
			strcpy_s(modelPath, 256, typedModelPath.c_str());
			ImGui::InputText("File Path", modelPath, 256);
			if (ImGui::IsItemDeactivatedAfterEdit())
			{
				typedModelPath = modelPath;
			}
			if (ImGui::Button("Load##1"))
			{
				mesh.ChangeMesh(modelPath);
			}
			std::string info = "Mesh Info: \n Vertex Count: " + std::to_string(mesh.m_vertices.size()) + "\n Index Count: " + std::to_string(mesh.m_indices.size());
			ImGui::Text(info.c_str());
			char materialPath[256] = "";
			strcpy_s(materialPath, 256, typedMaterialPath.c_str());
			ImGui::InputText("Material Path", materialPath, 256);
			if (ImGui::IsItemDeactivatedAfterEdit())
			{
				typedMaterialPath = materialPath;
			}
			if (ImGui::Button("Load##2"))
			{
				mesh.SetMaterial(materialPath);
			}
			MaterialGUI::DrawGUI(mesh.material);
			ImGui::TreePop();
		}
		else
		{
			typedModelPath = mesh.m_modelPath;
		}
	}
};

std::string MeshGUI::typedModelPath = "";
std::string MeshGUI::typedMaterialPath = "";