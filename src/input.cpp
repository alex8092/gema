#include "input.h"
#include "engine.h"
#include <iostream>
#include <functional>
#include <GLFW/glfw3.h>

using Gema::Input;
using Gema::Engine;

Input 			Input::_singleton;

void	Input::_key_handler(void *win, int key, int scancode, int action, int mods)
{
	(void)win;
	(void)scancode;
	(void)mods;
	Input *self = Input::singleton();
	bool	res = true;
	
	if (action == GLFW_PRESS)
	{
		for (auto it : self->_listeners)
		{
			if (!it->onKeyPressed(key))
				res = false;
		}
	}
	else if (action == GLFW_RELEASE)
	{
		for (auto it : self->_listeners)
		{
			if (!it->onKeyReleased(key))
				res = false;
		}
	}
	self->_continue = res;
}

void	Input::_mouse_move_handler(void *win, double x, double y)
{
	(void)win;
	Input *self = Input::singleton();
	double x2 = x - self->_mouse_pos_x;
	double y2 = y - self->_mouse_pos_y;
	self->_mouse_pos_x = x;
	self->_mouse_pos_y = y;
	for (auto it : self->_listeners)
		it->onMouseMove(x2, y2);
}

void	Input::_mouse_click_handler(void *win, int button, int action, int mods)
{
	(void)win;
	(void)mods;
	Input *self = Input::singleton();
	if (action == GLFW_PRESS)
	{
		for (auto it : self->_listeners)
			it->onMousePressed(button);
	}
	else if (action == GLFW_RELEASE)
	{
		for (auto it : self->_listeners)
			it->onMouseReleased(button);
	}
}

bool	Input::capture() noexcept
{
	if (!this->_glfw_handler_init)
	{
		glfwSetKeyCallback((GLFWwindow *)Engine::singleton()->window()->id(), (void	(*)(GLFWwindow *,int,int,int,int))Input::_key_handler);
		glfwSetCursorPosCallback((GLFWwindow *)Engine::singleton()->window()->id(), (void	(*)(GLFWwindow *,double,double))Input::_mouse_move_handler);
		glfwSetMouseButtonCallback((GLFWwindow *)Engine::singleton()->window()->id(), (void	(*)(GLFWwindow *,int,int,int))Input::_mouse_click_handler);
		this->_glfw_handler_init = true;
	}
	glfwPollEvents();
	return (this->_continue);
}

void	Input::setCursorVisible(bool visible) noexcept
{
	this->_cursor_visible = visible;
	if (this->_grab_cursor)
		return ;
	if (!visible)
		glfwSetInputMode((GLFWwindow *)Engine::singleton()->window()->id(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	else
		glfwSetInputMode((GLFWwindow *)Engine::singleton()->window()->id(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void	Input::setGrabCursor(bool grab) noexcept {
	this->_cursor_grab = grab;
	if (grab)
		glfwSetInputMode((GLFWwindow *)Engine::singleton()->window()->id(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	else
		this->setCursorVisible(this->_cursor_visible);
}