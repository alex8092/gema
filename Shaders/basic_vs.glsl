#version 150 core

in vec2 position;

out vec3 color;

void	main(void)
{
	color = vec3(1.0, 0.0, 0.0);
	gl_Position = vec4(position, 0.0, 1.0);
}