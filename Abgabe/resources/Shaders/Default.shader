name Default
#vert
#version 460

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vNormal;
layout(location = 2) in vec4 vColor;
layout(location = 3) in vec2 vTexcoord1;

out vec3 fNormal;
out vec4 fColor;

uniform mat4 u_MVP;
uniform mat4 u_ITM;

void main()
{
	gl_Position = u_MVP * vec4(vPosition.x, vPosition.y, vPosition.z, 1.0);
	fNormal = (u_ITM * vec4(vNormal, 0.0)).xyz;
}

#frag
#version 460

in vec3 fNormal;
in vec4 fColor;

out vec4 finalColor;

uniform vec4 u_Color;

void main()
{
	finalColor = u_Color;
}