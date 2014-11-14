#include "window.h"
#include "engine.h"

using Gema::Window;
using Gema::Engine;

bool		Window::_sdl_init = false;

Window::Window(const std::string& name, Engine *engine) :
	_name(name),
	_engine(engine)
{

}

Window::~Window() noexcept
{
	this->close();
	if (Window::_sdl_init)
	{
		SDL_Quit();
		Window::_sdl_init = false;
	}
}

bool	Window::_init_sdl() noexcept
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		this->_engine->setError(SDL_GetError());
		return (false);
	}
	this->_engine->render()->init();
	return (true);
}

bool	Window::_create_win() noexcept
{
	if (!Window::_sdl_init && !this->_init_sdl())
		return (false);
	Window::_sdl_init = true;
	this->_win = SDL_CreateWindow(this->_name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->_engine->render()->width(), this->_engine->render()->height(), SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	if (!this->_win)
	{
		this->_engine->setError(SDL_GetError());
		return (false);
	}
	this->_visible = true;
	this->_context = this->_engine->render()->createContext(this->_win);
	if (!this->_context)
	{
		this->close();
		return (false);
	}
	return (true);
}

bool	Window::show() noexcept
{
	if (!this->_win && !this->_create_win())
		return (false);
	if (this->_win && !this->_visible)
	{
		SDL_ShowWindow(this->_win);
		this->_visible = true;
	}
	return (this->_win);
}

bool	Window::hide() noexcept
{
	if (this->_win && this->_visible)
	{
		SDL_HideWindow(this->_win);
		this->_visible = false;
	}
	return (true);
}

void	Window::close() noexcept
{
	if (this->_win)
	{
		this->_engine->render()->destroyContext(this->_context);
		SDL_DestroyWindow(this->_win);
		this->_win = nullptr;
	}
}

void	Window::centerCursor() const noexcept
{
	SDL_WarpMouseInWindow(this->_win, this->_engine->render()->width() / 2, this->_engine->render()->height() / 2);
}

bool	Window::isCenteredCursor(int16_t x, int16_t y) const noexcept
{
	return (x == (int16_t)this->_engine->render()->width() / 2 && y == (int16_t)this->_engine->render()->height() / 2);
}

bool	Window::update() noexcept
{
	return (this->_engine->render()->renderFrame(this->_win));
}

void	Window::setFullscreen(bool full) const noexcept
{
	SDL_SetWindowFullscreen(this->_win, (full) ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
}