#include "engine.h"

using Gema::Engine;
using Gema::Window;

Engine::Engine() :
	_render(this)
{

}

bool	Engine::init(const std::string& appName) noexcept
{
	if (!this->_win)
	{
		this->_win = new Window(appName, this);
		this->_input.setWindow(this->_win);
		if (!this->_win->show())
			return (false);
		this->_input.setCursorVisible(false);
		this->_input.setGrabCursor();
		this->_win->centerCursor();
		// this->_win->setFullscreen();
	}
	return (true);
}

bool	Engine::start() noexcept
{
	while (!this->_win->isClose())
	{
		if (!this->_input.capture() || !this->_win->update())
			this->_win->close();
	}
	return (true);
}