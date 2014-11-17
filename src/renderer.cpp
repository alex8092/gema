#include "renderer.h"
#include "engine.h"
#include "shader.h"
#include "mat4.h"
#include "vec3.h"
#include "mesh.h"
#include <iostream>
#include <GLFW/glfw3.h>

using Gema::Renderer;
using Gema::Window;
using Gema::Engine;
using Gema::Shader;
using Gema::mat4;
using Gema::vec3;
using Gema::Mesh;

bool	Renderer::_glew_init = false;

Renderer 	Renderer::_singleton;

Renderer::Renderer() noexcept
{

}

Renderer::~Renderer()
{
}

bool			Renderer::render(void) noexcept
{
	static Shader	shad("Shaders/basic_vs.glsl", "Shaders/basic_fs.glsl");
	static mat4		modelview, projection;
	static float 	ang = 0.001;
	static Mesh		*mesh = nullptr;

	double		current = glfwGetTime();
	this->_diff_time = current - this->_last_ticks;
	this->_last_ticks = current;

	if (!Renderer::_glew_init)
	{
		glewExperimental = GL_TRUE;
		GLenum error = glewInit();
		if (error != GLEW_OK)
			return (false);
		Renderer::_glew_init = true;
		glEnable(GL_DEPTH_TEST);
	}

	if (!shad.isLoad())
	{
		if (!shad.load())
			return (false);
		projection.perspective(70.0, (double)this->_width / (double)this->_height, 1.0, 1000.0);
		mesh = Mesh::get("Cube");
	}
	this->_cam.update();
	modelview.lookAt(this->_cam.position(), this->_cam.target(), this->_cam.up());
	ang += 0.01;
	if (ang > 3.14)
		ang = 0.01;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(shad.id());
	glUniformMatrix4fv(shad.uniformLocation("projection"), 1, GL_FALSE, projection.values());
	glUniformMatrix4fv(shad.uniformLocation("modelview"), 1, GL_FALSE, modelview.values());
	if (mesh)
		mesh->draw();
	glUseProgram(0);
	Engine::singleton()->window()->swapBuffers();
	return (true);
}
