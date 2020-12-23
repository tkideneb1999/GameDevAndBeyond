#version 460

in vec3 fNormal;
in vec4 fColor;

out vec4 finalColor;

uniform vec3 u_MainLightDir;

void main()
{
	float lambert = clamp(dot(fNormal, u_MainLightDir), 0, 1);
	finalColor = vec4(1.0, 0.0, 0.0, 1.0);
}