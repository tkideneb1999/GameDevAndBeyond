#version 460

in vec3 fNormal;
in vec4 fColor;

out vec4 finalColor;

uniform vec3 u_MainLightDir;

void main()
{
	
	finalColor = vec4(fNormal * 0.5 + 0.5, 1.0);
}