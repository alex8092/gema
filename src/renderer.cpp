#include "renderer.h"
#include "engine.h"
#include "shader.h"
#include <iostream>

using Gema::Renderer;
using Gema::Window;
using Gema::Engine;
using Gema::Shader;

bool	Renderer::_glew_init = false;

Renderer::Renderer(Engine *engine) noexcept :
	_engine(engine)
{

}

void	Renderer::init() const noexcept
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, this->_major_version);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, this->_minor_version);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, (this->_double_buffer) ? 1 : 0);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, this->_depth);
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
	}
	return (context);
}

void			Renderer::destroyContext(SDL_GLContext context) const noexcept
{
	SDL_GL_DeleteContext(context);
}

bool			Renderer::renderFrame(SDL_Window *win) noexcept
{
	static float vertices[] =
	{
		-0.5, -0.5,
		0, 0.5,
		0.5, -0.5
	};
	static Shader	shad("Shaders/basic_vs.glsl", "Shaders/basic_fs.glsl");

	if (!shad.isLoad())
	{
		shad.setLocation(0, "position");
		if (!shad.load())
			return (false);
	}
	glClear(GL_COLOR_BUFFER_BIT);
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
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, vertices);
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(0);
	glUseProgram(0);
	// glDisableVertexAttribArray(1);
	// glBindBuffer(GL_ARRAY_BUFFER, 0);
	// glDeleteBuffers(1, &vbo);
	// glDeleteBuffers(1, &vbo2);
	SDL_GL_SwapWindow(win);
	return (true);
}