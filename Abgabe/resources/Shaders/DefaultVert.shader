#version 460

layout(location = 0) in vec3 Position;

out vec4 Color;

uniform float gScale;
uniform mat4 gModel;

void main()
{
	gl_Position = gModel * vec4(0.5 * Position.x * gScale, 0.5 * Position.y * gScale, Position.z, 1.0);
	Color = vec4(clamp(Position, 0.0, 1.0), 1.0);
}