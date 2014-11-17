#ifndef GEMA_INPUT_H
# define GEMA_INPUT_H

# include <GL/glew.h>
# include <vector>
# include <map>
# include "window.h"

namespace Gema
{
	struct InputListener
	{
		virtual	void	onMouseMove(double xRel, double yRel) noexcept = 0;
		virtual	void	onMousePressed(uint8_t button) noexcept = 0;
		virtual void	onMouseReleased(uint8_t button) noexcept = 0;
		virtual bool	onKeyPressed(int code) noexcept = 0;
		virtual bool	onKeyReleased(int code) noexcept = 0;
	};

	class Input
	{
	private:
		std::vector<InputListener *>	_listeners;
		double							_mouse_pos_x = 0;
		double							_mouse_pos_y = 0;
		bool							_cursor_visible = true;
		bool							_cursor_grab = false;
		bool							_grab_cursor = false;
		bool							_glfw_handler_init = false;
		static Input 					_singleton;
		static void						_key_handler(void *win, int key, int scancode, int action, int mods);
		static void						_mouse_move_handler(void *win, double x, double y);
		static void						_mouse_click_handler(void *win, int button, int action, int mods);
		bool							_continue = true;
		explicit 						Input() = default;

	public:
		virtual					~Input() noexcept = default;
		bool					capture() noexcept;

		static inline Input 	*singleton() noexcept {
			return (&Input::_singleton);
		}	

		inline void				addListener(InputListener *listener) noexcept {
			this->_listeners.push_back(listener);
		}

		inline double			mouseX() const noexcept {
			return (this->_mouse_pos_x);
		}

		inline double			mouseY() const noexcept {
			return (this->_mouse_pos_y);
		}

		void					setCursorVisible(bool visible = true) noexcept; 
		void					setGrabCursor(bool grab = true) noexcept;
	};
}

#endif