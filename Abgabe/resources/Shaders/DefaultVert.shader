#version 460

layout(location = 0) in vec3 Position;

uniform float gScale;

void main()
{
	gl_Position = vec4(0.5 * Position.x * gScale, 0.5 * Position.y * gScale, Position.z, 1.0);
}