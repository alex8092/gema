#include "input.h"

using Gema::Input;
#include <iostream>

bool	Input::capture() noexcept
{
	SDL_Event ev;

	while (SDL_PollEvent(&ev))
	{
		switch (ev.type)
		{
			case SDL_WINDOWEVENT:
			{
				if (ev.window.event == SDL_WINDOWEVENT_CLOSE)
					return (false);
				break ;
			}
			case SDL_MOUSEMOTION:
			{
				if (this->_win && this->_win->isCenteredCursor(ev.motion.x, ev.motion.y) && this->_grab_cursor)
					break ;
				this->_mouse_pos_x = ev.motion.x;
				this->_mouse_pos_y = ev.motion.y;
				for (auto it : this->_listeners)
					it->onMouseMove(ev.motion.xrel, ev.motion.yrel);
				if (this->_win && this->_grab_cursor)
					this->_win->centerCursor();
				break ;
			}
			case SDL_KEYDOWN:
			{
				bool	res = true;
				bool	isPress = false;
				SDL_Scancode code = ev.key.keysym.scancode;
				auto it = this->_keymap.find(code);
				if (it == this->_keymap.end())
					this->_keymap[code] = true;
				else
				{
					isPress = it->second;
					it->second = true;
				}
				if (isPress)
				{
					auto it2 = this->_keyrepeat.find(code);
					if (it2 == this->_keyrepeat.end())
						this->_keyrepeat[code] = false;
				}
				if (!isPress || (isPress && this->_keyrepeat[code]))
				{
					for (auto it : this->_listeners)
					{
						if (!it->onKeyPressed(code))
							res = false;
					}
				}
				return (res);
			}
			case SDL_KEYUP:
			{
				bool res = true;
				SDL_Scancode code = ev.key.keysym.scancode;
				this->_keymap[code] = false;
				for (auto it : this->_listeners)
				{
					if (!it->onKeyReleased(code))
						res = false;
				}
				return (res);
			}
			case SDL_MOUSEBUTTONDOWN:
			{
				for (auto it : this->_listeners)
					it->onMousePressed(ev.button.button);
				break ;
			}
			case SDL_MOUSEBUTTONUP:
			{
				for (auto it : this->_listeners)
					it->onMouseReleased(ev.button.button);
				break ;
			}
		}
	}
	return (true);
}