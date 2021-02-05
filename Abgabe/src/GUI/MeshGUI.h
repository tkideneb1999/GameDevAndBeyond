#pragma once

#include "ImGui/imgui.h"

#include "../Rendering/Mesh.h"

class MeshGUI
{
public:
	static void DrawGUI(Mesh& mesh)
	{
		ImGui::Separator();
		std::string info = "Mesh Info: \n Vertex Count: " + std::to_string(mesh.m_vertices.size()) + "\n Index Count: " + std::to_string(mesh.m_indices.size());
		ImGui::Text(info.c_str());
	}
};