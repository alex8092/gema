#version 150 core

in vec3 position;

out vec3 color;

uniform mat4 projection;
uniform mat4 modelview;

void	main(void)
{
	color = vec3(1.0, 0.0, 0.0);
	gl_Position = projection * modelview * vec4(position, 1.0);
}