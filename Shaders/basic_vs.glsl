#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

uniform mat4 projection;
uniform mat4 model;
uniform mat4 view;

out vec3 oNormal;
out vec3 oPosition;

void	main(void)
{
	oPosition = position;
	gl_Position = projection * model * view * vec4(position, 1.0);
	oNormal = normal;
}