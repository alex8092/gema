#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

layout (std140) uniform Matrices
{
	mat4 projection;
	mat4 modelview;
};

out vec4 color;

void	main(void)
{
	gl_Position = projection * modelview * vec4(position, 1.0);
	color = vec4(1.0, 1.0, 1.0, 1.0);
}