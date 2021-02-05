#pragma once

#include "ImGui/imgui.h"

#include "../Rendering/Transform.h"

class TransformGUI
{
public:
	static void DrawGUI(Transform& transform)
	{
		ImGui::Separator();
		ImGui::Text("Transform");
		ImGui::InputFloat3("Translation", &(transform.m_Position[0]));
		ImGui::InputFloat4("Rotation", &(transform.m_Rotation[0]));
		ImGui::InputFloat3("Scale", &(transform.m_Scale[0]));
	}
};