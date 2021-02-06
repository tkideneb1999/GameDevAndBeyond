#pragma once

#include "ImGui/imgui.h"

#include "../Rendering/Transform.h"

class TransformGUI
{
public:
	static void DrawGUI(Transform& transform)
	{
		ImGui::Separator();
		if (ImGui::TreeNode("Transform"))
		{
			ImGui::DragFloat3("Translation", &(transform.m_Position[0]), 0.5f, -100.0f, 100.0f);
			bool translationChanged = ImGui::IsItemEdited();

			ImGui::DragFloat4("Rotation", &(transform.m_Rotation[0]), 0.5f, -100.0f, 100.0f);
			bool rotationChanged = ImGui::IsItemEdited();

			ImGui::DragFloat3("Scale", &(transform.m_Scale[0]), 0.5f, -100.0f, 100.0f);
			bool scaleChanged = ImGui::IsItemEdited();

			if (translationChanged || rotationChanged || scaleChanged)
				transform.ConstructMatrix();

			ImGui::TreePop();
		}
	}
};