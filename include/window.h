#ifndef GEMA_WINDOW_H
# define GEMA_WINDOW_H

# include <GL/glew.h>
# include <GLFW/glfw3.h>
# include <stdint.h>
# include <string>

namespace Gema
{
	class Engine;

	class Window
	{
	private:
		static bool		_lib_init;

		GLFWwindow		*_win = nullptr;

		std::string		_name;
		Engine			*_engine;
		bool			_visible = false;

		bool		_init_lib() noexcept;

		bool		_create_win() noexcept;

	public:
		explicit 	Window(const std::string& name, Engine *engine);
		virtual		~Window() noexcept;

		bool		show() noexcept;
		bool		hide() noexcept;
		void		close() noexcept;

		bool		update() noexcept;

		void		setFullscreen(bool full = true) const noexcept;

		inline bool	isClose() const noexcept {
			return (this->_win == nullptr);
		}
		inline GLFWwindow *id() const noexcept {
			return (this->_win);
		}
	};
}

#endif