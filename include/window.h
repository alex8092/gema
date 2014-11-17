#ifndef GEMA_WINDOW_H
# define GEMA_WINDOW_H

# include <GL/glew.h>
# include <stdint.h>
# include <string>

namespace Gema
{
	class Engine;

	class Window
	{
	private:
		static bool		_lib_init;
		bool			_fullscreen;

		void			*_win = nullptr;

		std::string		_name;
		bool			_visible = false;

		bool			_init_lib() noexcept;
		bool			_create_win() noexcept;

	public:
		explicit 		Window(const std::string& name, bool fullscreen = true);
		virtual			~Window() noexcept;

		bool			show() noexcept;
		void			close() noexcept;
		bool			update() noexcept;
		void			setFullscreen(bool full = true) const noexcept;
		void			swapBuffers() const noexcept;

		inline void 	*id() const noexcept {
			return (this->_win);
		}

		inline bool		isClose() const noexcept {
			return (this->_win == nullptr);
		}
	};
}

#endif