#include "window.h"
#include "renderer.h"
#include "engine.h"
#include <functional>
#include <algorithm>
#include <GLFW/glfw3.h>

using Gema::Window;
using Gema::Renderer;
using Gema::Engine;

bool		Window::_lib_init = false;

Window::Window(const std::string& name, bool fullscreen) :
	_fullscreen(fullscreen),
	_name(name)
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

static void error(int errnumber, const char *description) {
	(void)errnumber;
	Engine::singleton()->setError(description);
}

bool	Window::_init_lib() noexcept
{
	glfwSetErrorCallback(error);
	if (!glfwInit())
		return (false);
	#ifdef __APPLE__
	    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	#endif
	return (true);
}

bool	Window::_create_win() noexcept
{
	if (!Window::_lib_init && !this->_init_lib())
		return (false);
	Window::_lib_init = true;
	this->_win = glfwCreateWindow(800, 600, this->_name.c_str(), (!this->_fullscreen) ? NULL : glfwGetPrimaryMonitor(), NULL);
	if (!this->_win)
		return (false);
	glfwMakeContextCurrent((GLFWwindow *)this->_win);
	return (true);
}

bool	Window::show() noexcept
{
	if (!this->_win && !this->_create_win())
		return (false);
	return (this->_win);
}

void	Window::close() noexcept
{
	if (this->_win)
	{
		glfwDestroyWindow((GLFWwindow *)this->_win);
		this->_win = nullptr;
	}
}

bool	Window::update() noexcept
{
	return (Renderer::singleton()->render());
}

void	Window::setFullscreen(bool full) const noexcept
{
	// at construct time, i've to find a way on runtime
	(void)full;
}

void	Window::swapBuffers() const noexcept {
	glfwSwapBuffers((GLFWwindow *)this->_win);
}