#ifndef GEMA_RENDERER_H
# define GEMA_RENDERER_H

# include <stdint.h>
# include <SDL2/SDL.h>
# define GL3_PROTOTYPE
# include <GL/glew.h>
# include <GL/gl.h>

namespace Gema
{
	class Engine;

	class Renderer
	{
	private:
		Engine		*_engine = nullptr;
		uint32_t	_width = 800;
		uint32_t	_height = 600;
		int32_t		_major_version = 3;
		int32_t		_minor_version = 1;
		uint32_t	_depth = 24;
		bool		_double_buffer = true;

	public:
		explicit 		Renderer(Engine *engine) noexcept;
		virtual 		~Renderer() noexcept = default;

		inline uint32_t	width() const noexcept {
			return (this->_width);
		}

		inline uint32_t height() const noexcept {
			return (this->_height);
		}

		void			init() const noexcept;
		SDL_GLContext	createContext(SDL_Window *win) const noexcept;
		void			destroyContext(SDL_GLContext context) const noexcept;
		bool			renderFrame(SDL_Window *win) noexcept;
	};
}

#endif