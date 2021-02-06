#pragma once

#include "ImGui/imgui.h"
#include "../Rendering/Camera.h"

class CameraGUI
{
public:
	static void DrawGUI(Camera& camera)
	{
		ImGui::Separator();
		if (ImGui::TreeNode("Camera"))
		{
			ImGui::SliderFloat("FOV Y", &camera.fovYangle, 1.0f, 180.0f);
			bool fovYchaned = ImGui::IsItemEdited();

			ImGui::DragFloat("Near Plane", &camera.zNear, 0.5f, 0.0f, 10.0f);
			bool zNearChanged = ImGui::IsItemEdited();

			ImGui::DragFloat("Far Plane", &camera.zFar, 1.0f, camera.zNear, 1000.0f);
			bool zFarChanged = ImGui::IsItemEdited();
			
			if (fovYchaned || zNearChanged || zFarChanged)
				camera.ApplyCameraData();

			ImGui::TreePop();
		}
	}
};