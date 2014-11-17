#include "window.h"
#include "engine.h"
#include <functional>
#include <algorithm>

using Gema::Window;
using Gema::Engine;

bool		Window::_lib_init = false;

Window::Window(const std::string& name, Engine *engine) :
	_name(name),
	_engine(engine)
{

}

Window::~Window() noexcept
{
	this->close();
	if (Window::_lib_init)
	{
		glfwTerminate();
		Window::_lib_init = false;
	}
}

static void error(int error, const char *description)
{
	(void)error;
	std::cerr << "error: " << description << std::endl;
}

bool	Window::_init_lib() noexcept
{
	glfwSetErrorCallback(error);
	if (!glfwInit())
		return (false);
	this->_engine->render()->init();
	return (true);
}

bool	Window::_create_win() noexcept
{
	if (!Window::_lib_init && !this->_init_lib())
		return (false);
	Window::_lib_init = true;
	this->_engine->render()->init();
	this->_win = glfwCreateWindow(800, 600, this->_name.c_str(), NULL /* FULLSCREEN glfwGetPrimaryMonitor() */, NULL);
	if (!this->_win)
		return (false);
	glfwMakeContextCurrent(this->_win);
	return (true);
}

bool	Window::show() noexcept
{
	if (!this->_win && !this->_create_win())
		return (false);
	return (this->_win);
}

bool	Window::hide() noexcept
{
	return (true);
}

void	Window::close() noexcept
{
	if (this->_win)
	{
		glfwDestroyWindow(this->_win);
		this->_win = nullptr;
	}
}

bool	Window::update() noexcept
{
	return (this->_engine->render()->renderFrame(this->_win));
}

void	Window::setFullscreen(bool full) const noexcept
{
	// at construct time, i've to find a way on runtime
	(void)full;
}