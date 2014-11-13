#ifndef GEMA_INPUT_H
# define GEMA_INPUT_H

# include <SDL2/SDL.h>
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
		virtual bool	onKeyPressed(SDL_Scancode code) noexcept = 0;
		virtual bool	onKeyReleased(SDL_Scancode code) noexcept = 0;
	};

	class Input
	{
	private:
		std::map<SDL_Scancode, bool>	_keyrepeat;
		std::map<SDL_Scancode, bool>	_keymap;
		std::vector<InputListener *>	_listeners;
		int32_t							_mouse_pos_x = 0;
		int32_t							_mouse_pos_y = 0;
		Window							*_win = nullptr;
		bool							_grab_cursor = false;

	public:
		explicit 		Input() = default;
		virtual			~Input() noexcept = default;
		bool			capture() noexcept;

		inline void		addListener(InputListener *listener) noexcept {
			this->_listeners.push_back(listener);
		}
		inline void		setKeyRepeat(SDL_Scancode code, bool repeat = true) noexcept {
			this->_keyrepeat[code] = repeat;
		}

		inline int32_t	mouseX() const noexcept {
			return (this->_mouse_pos_x);
		}

		inline int32_t	mouseY() const noexcept {
			return (this->_mouse_pos_y);
		}

		inline void		setCursorVisible(bool visible = true) const noexcept {
			SDL_ShowCursor((visible) ? SDL_ENABLE : SDL_DISABLE);
		}

		inline void		setGrabCursor(bool grab = true) noexcept {
			this->_grab_cursor = grab;
		}

		inline void		setWindow(Window *win) noexcept {
			this->_win = win;
		}
	};
}

#endif