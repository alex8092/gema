#include "renderer.h"
#include "engine.h"

using Gema::Renderer;
using Gema::Window;
using Gema::Engine;

Renderer::Renderer(Engine *engine) noexcept :
	_engine(engine)
{}

void	Renderer::init() const noexcept
{
	glewInit();
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
	return (context);
}

void			Renderer::destroyContext(SDL_GLContext context) const noexcept
{
	SDL_GL_DeleteContext(context);
}

bool			Renderer::renderFrame(SDL_Window *win) noexcept
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	SDL_GL_SwapWindow(win);
	return (true);
}