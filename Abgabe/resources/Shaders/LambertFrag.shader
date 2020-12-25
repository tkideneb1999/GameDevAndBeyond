#version 460

in vec3 fNormal;

out vec4 finalColor;

uniform vec3 u_LightDir;
uniform vec4 u_Color;

void main()
{
	float lambert = dot(fNormal, u_LightDir);
	finalColor = u_Color * lambert;
}