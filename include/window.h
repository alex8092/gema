#ifndef GEMA_WINDOW_H
# define GEMA_WINDOW_H

# include <SDL2/SDL.h>
# include <stdint.h>
# include <string>

namespace Gema
{
	class Engine;

	class Window
	{
	private:
		static bool		_sdl_init;

		SDL_Window		*_win = nullptr;
		SDL_GLContext	_context;
		std::string		_name;
		Engine			*_engine;
		bool			_visible = false;

		bool		_init_sdl() noexcept;

		bool		_create_win() noexcept;

	public:
		explicit 	Window(const std::string& name, Engine *engine);
		virtual		~Window() noexcept;

		bool		show() noexcept;
		bool		hide() noexcept;
		void		close() noexcept;

		void		centerCursor() const noexcept;

		bool		isCenteredCursor(int16_t x, int16_t y) const noexcept;

		bool		update() noexcept;

		void		setFullscreen(bool full = true) const noexcept;

		inline bool	isClose() const noexcept {
			return (this->_win == nullptr);
		}
	};
}

#endif