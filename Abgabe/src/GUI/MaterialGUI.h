#pragma once

#include "ImGui/imgui.h"

#include "../Rendering/Material.h"

class MaterialGUI
{
public:
	static void DrawGUI(Material& material)
	{
		if (ImGui::TreeNode("Material"))
		{
			ImGui::Text(material.m_Name.c_str());
			if (ImGui::Selectable(material.GetShader()->GetName().c_str()))
			{
				ImGui::OpenPopup("Select Shader");
			}
			if (ImGui::BeginPopup("Select Shader"))
			{
				std::vector<std::string> shaderNames;
				ShaderManager::Get().GetShaderNames(shaderNames);
				for (auto& shaderName : shaderNames)
				{
					if (ImGui::Selectable(shaderName.c_str()))
					{
						material.SetShader(shaderName);
						ImGui::CloseCurrentPopup();
					}
				}
				ImGui::EndPopup();
			}

			//iUniforms
			if (material.m_iUniforms.size() > 0)
			{
				if (ImGui::TreeNode("Integer Parameters"))
				{
					for (auto& iUniform : material.m_iUniforms)
					{
						ImGui::DragInt(iUniform.first.c_str(), &iUniform.second, 2.0f, -10, 10);
					}
					ImGui::TreePop();
				}
			}

			//fUniforms
			if (material.m_fUniforms.size() > 0)
			{
				if (ImGui::TreeNode("Float Parameters"))
				{
					for (auto& fUniform : material.m_fUniforms)
					{
						ImGui::DragFloat(fUniform.first.c_str(), &fUniform.second, 2.0f, -10.0f, 10.0f);
					}
					ImGui::TreePop();
				}
			}

			//v2Uniforms
			if (material.m_v2Uniforms.size() > 0)
			{
				if (ImGui::TreeNode("Vector2 Parameters"))
				{
					for (auto& v2Uniform : material.m_v2Uniforms)
					{
						ImGui::DragFloat2(v2Uniform.first.c_str(), &v2Uniform.second[0], 2.0f, -10.0f, 10.0f);
					}
					ImGui::TreePop();
				}
			}

			//v3Uniforms
			if (material.m_v3Uniforms.size() > 0)
			{
				if (ImGui::TreeNode("Vector3 Parameters"))
				{
					for (auto& v3Uniform : material.m_v3Uniforms)
					{
						ImGui::DragFloat3(v3Uniform.first.c_str(), &v3Uniform.second[0], 2.0f, -10.0f, 10.0f);
					}
					ImGui::TreePop();
				}
			}

			//v4Uniforms
			if (material.m_v4Uniforms.size() > 0)
			{
				if (ImGui::TreeNode("Vector4 Parameters"))
				{
					for (auto& v4Uniform : material.m_v4Uniforms)
					{
						ImGui::DragFloat4(v4Uniform.first.c_str(), &v4Uniform.second[0], 2.0f, -10.0f, 10.0f);
					}
					ImGui::TreePop();
				}
			}

			ImGui::TreePop();
		}
	}
};