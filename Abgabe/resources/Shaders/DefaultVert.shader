#version 460

layout(location = 0) in vec3 Position;
layout(location = 1) in vec3 Normal;
layout(location = 2) in vec4 VertexColor;
layout(location = 3) in vec2 Texcoord1;

out vec4 Color;

uniform mat4 gMVP;

void main()
{
	gl_Position = gMVP * vec4(Position.x, Position.y, Position.z, 1.0);
	Color = vec4(1.0, 1.0, 1.0, 1.0);
}