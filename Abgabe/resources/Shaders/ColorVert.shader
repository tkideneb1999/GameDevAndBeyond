#version 460

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vNormal;
layout(location = 2) in vec4 vColor;
layout(location = 3) in vec2 vTexcoord1;


uniform mat4 u_MVP;
uniform mat4 u_ITM;

void main()
{
	gl_Position = u_MVP * vec4(vPosition, 1.0);
}