#include "input.h"
#include <iostream>
#include <functional>

using Gema::Input;

Input 			*Input::_current = nullptr;

void	Input::_key_handler(GLFWwindow *win, int key, int scancode, int action, int mods)
{
	(void)win;
	(void)scancode;
	(void)mods;
	Input *self = Input::_current;
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

void	Input::_mouse_move_handler(GLFWwindow *win, double x, double y)
{
	(void)win;
	Input *self = Input::_current;
	double x2 = x - self->_mouse_pos_x;
	double y2 = y - self->_mouse_pos_y;
	self->_mouse_pos_x = x;
	self->_mouse_pos_y = y;
	for (auto it : self->_listeners)
		it->onMouseMove(x2, y2);
}

void	Input::_mouse_click_handler(GLFWwindow *win, int button, int action, int mods)
{
	(void)win;
	(void)mods;
	Input *self = Input::_current;
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
		Input::_current = this;
		glfwSetKeyCallback(this->_win->id(), Input::_key_handler);
		glfwSetCursorPosCallback(this->_win->id(), Input::_mouse_move_handler);
		glfwSetMouseButtonCallback(this->_win->id(), Input::_mouse_click_handler);
		this->_glfw_handler_init = true;
	}
	Input::_current = this;
	glfwPollEvents();
	return (this->_continue);
}