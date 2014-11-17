#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

uniform vec3 ambient;
uniform vec3 diffuse;
uniform vec3 specular;
uniform mat4 projection;
uniform mat4 modelview;

out vec4 color;

void	main(void)
{
	gl_Position = projection * modelview * vec4(position, 1.0);
	color = vec4(ambient, 1.0);
}