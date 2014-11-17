#ifndef GEMA_INPUT_H
# define GEMA_INPUT_H

# include <GL/glew.h>
# include <GLFW/glfw3.h>
# include <vector>
# include <map>
# include "window.h"

namespace Gema
{
	struct InputListener
	{
		virtual	void	onMouseMove(int16_t xRel, int16_t yRel) noexcept = 0;
		virtual	void	onMousePressed(uint8_t button) noexcept = 0;
		virtual void	onMouseReleased(uint8_t button) noexcept = 0;
		virtual bool	onKeyPressed(int code) noexcept = 0;
		virtual bool	onKeyReleased(int code) noexcept = 0;
	};

	class Input
	{
	private:
		std::map<int, bool>				_keyrepeat;
		std::map<int, bool>				_keymap;
		std::vector<InputListener *>	_listeners;
		double							_mouse_pos_x = 0;
		double							_mouse_pos_y = 0;
		bool							_cursor_visible = true;
		bool							_cursor_grab = false;
		Window							*_win = nullptr;
		bool							_grab_cursor = false;
		bool							_glfw_handler_init = false;
		static Input 					*_current;
		static void						_key_handler(GLFWwindow *win, int key, int scancode, int action, int mods);
		static void						_mouse_move_handler(GLFWwindow *win, double x, double y);
		static void						_mouse_click_handler(GLFWwindow *win, int button, int action, int mods);
		bool							_continue = true;

	public:
		explicit 		Input() = default;
		virtual			~Input() noexcept = default;
		bool			capture() noexcept;

		inline void		addListener(InputListener *listener) noexcept {
			this->_listeners.push_back(listener);
		}
		inline void		setKeyRepeat(int code, bool repeat = true) noexcept {
			this->_keyrepeat[code] = repeat;
		}

		inline double	mouseX() const noexcept {
			return (this->_mouse_pos_x);
		}

		inline double	mouseY() const noexcept {
			return (this->_mouse_pos_y);
		}

		inline void		setCursorVisible(bool visible = true) noexcept {
			this->_cursor_visible = visible;
			if (this->_grab_cursor)
				return ;
			if (!visible)
				glfwSetInputMode(this->_win->id(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
			else
				glfwSetInputMode(this->_win->id(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}

		inline void		setGrabCursor(bool grab = true) noexcept {
			this->_cursor_grab = grab;
			if (grab)
				glfwSetInputMode(this->_win->id(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			else
				this->setCursorVisible(this->_cursor_visible);
		}

		inline void		setWindow(Window *win) noexcept {
			this->_win = win;
		}
	};
}

#endif