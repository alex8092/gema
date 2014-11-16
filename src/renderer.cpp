#include "renderer.h"
#include "engine.h"
#include "shader.h"
#include "mat4.h"
#include "vec3.h"
#include "mesh.h"
#include <iostream>

using Gema::Renderer;
using Gema::Window;
using Gema::Engine;
using Gema::Shader;
using Gema::mat4;
using Gema::vec3;
using Gema::Mesh;

bool	Renderer::_glew_init = false;

Renderer::Renderer(Engine *engine) noexcept :
	_engine(engine)
{

}

Renderer::~Renderer()
{
}

void	Renderer::init() const noexcept
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, this->_major_version);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, this->_minor_version);
#ifdef __APPLE__
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
#endif
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, (this->_double_buffer) ? 1 : 0);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, this->_depth);
    glGetString(GL_VERSION);
}

SDL_GLContext	Renderer::createContext(SDL_Window *win) const noexcept
{
	SDL_GLContext	context = nullptr;

	context = SDL_GL_CreateContext(win);
	if (!context)
	{
		this->_engine->setError(SDL_GetError());
		return (0);
	}
	if (!Renderer::_glew_init)
	{
		GLenum error = glewInit();
		if (error != GLEW_OK)
		{
			SDL_GL_DeleteContext(context);
			return (0);
		}
		Renderer::_glew_init = true;
		glEnable(GL_DEPTH_TEST);
		std::cout << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
	}
	return (context);
}

void			Renderer::destroyContext(SDL_GLContext context) const noexcept
{
	SDL_GL_DeleteContext(context);
}

bool			Renderer::renderFrame(SDL_Window *win) noexcept
{
	static Shader	shad("Shaders/basic_vs.glsl", "Shaders/basic_fs.glsl");
	static mat4		modelview, projection;
	static float 	ang = 0.001;
	static Mesh		*mesh = nullptr;

	uint32_t		current = SDL_GetTicks();
	this->_diff_time = current - this->_last_ticks;
	this->_last_ticks = current;

	if (!shad.isLoad())
	{
		shad.setLocation(0, "position");
		shad.setLocation(1, "normal");
		if (!shad.load())
			return (false);
		projection.perspective(70.0, (double)this->_width / (double)this->_height, 1.0, 1000.0);
		// mesh = new Mesh();
		// mesh->vertices().push_back(vec3(0, 0, 0));
		// mesh->vertices().push_back(vec3(1, 0, 0));
		// mesh->vertices().push_back(vec3(0, 1, 0));
		// mesh->vertices().push_back(vec3(1, 1, 0));
		// mesh->indices().push_back(0);
		// mesh->indices().push_back(1);
		// mesh->indices().push_back(2);
		// mesh->indices().push_back(1);
		// mesh->indices().push_back(2);
		// mesh->indices().push_back(3);
		mesh = Mesh::get("Cube");
	}
	this->_cam.update();
	modelview.lookAt(this->_cam.position(), this->_cam.target(), this->_cam.up());
	// modelview.rotate(vec3(0, 1, 0), ang);
	ang += 0.01;
	if (ang > 3.14)
		ang = 0.01;

	// mat4 trans;
	// trans.translate(vec3(0, ang * -1, 0));
	// modelview *= trans;

	// glm::mat4 	proj = (glm::mat4)glm::perspective(70.0, (double)this->_width / (double)this->_height, 1.0, 1000.0);
	// mod = (glm::mat4)glm::translate(mod, glm::vec3(2, 0, 0));
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// GLuint vbo;
	// GLuint vbo2;
	// glGenBuffers(1, &vbo2);
	// glBindBuffer(GL_ARRAY_BUFFER, vbo2);
	// glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), colors, GL_STATIC_DRAW);
	// glVertexAttribPointer(1, 3, GL_UNSIGNED_INT, GL_FALSE, 0, colors);
	// glEnableVertexAttribArray(1);
	// glGenBuffers(1, &vbo);
	// glBindBuffer(GL_ARRAY_BUFFER, vbo);
	// glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), vertices, GL_STATIC_DRAW);
	glUseProgram(shad.id());
	glUniformMatrix4fv(shad.uniformLocation("projection"), 1, GL_FALSE, projection.values());
	glUniformMatrix4fv(shad.uniformLocation("modelview"), 1, GL_FALSE, modelview.values());
	// glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vertices);
	// glEnableVertexAttribArray(0);
	// glDrawArrays(GL_TRIANGLES, 0, 3);
	// glDisableVertexAttribArray(0);
	if (mesh)
		mesh->draw();
	glUseProgram(0);
	// glDisableVertexAttribArray(1);
	// glBindBuffer(GL_ARRAY_BUFFER, 0);
	// glDeleteBuffers(1, &vbo);
	// glDeleteBuffers(1, &vbo2);
	SDL_GL_SwapWindow(win);
	return (true);
}
