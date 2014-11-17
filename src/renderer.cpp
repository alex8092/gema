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
	static Mesh		*mesh = nullptr, *mesh2 = nullptr, *mesh3 = nullptr;

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

	if (mesh == nullptr)
	{
		this->_proj.perspective(70.0, (double)this->_width / (double)this->_height, 1.0, 1000.0);
		mesh = Mesh::get("Cube");
		mesh2 = Mesh::get("Sphere");
		mesh3 = Mesh::get("Plane");
	}
	this->_cam.update();
	this->_view.lookAt(this->_cam.position(), this->_cam.target(), this->_cam.up());
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (!mesh || !mesh->draw())
		return (false);
	if (!mesh2 || !mesh2->draw())
		return (false);
	if (!mesh3 || !mesh3->draw())
		return (false);
	Engine::singleton()->window()->swapBuffers();
	return (true);
}
