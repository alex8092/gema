#ifndef GEMA_RENDERER_H
# define GEMA_RENDERER_H

# include <stdint.h>
# include <GL/glew.h>

# include <GLFW/glfw3.h>

# define GL3_PROTOTYPES 1

# ifdef __APPLE__
#  include <OpenGL/gl.h>
# else
#  include <GL/gl.h>
# endif

# include "scene.h"
# include "camera.h"

namespace Gema
{
	class Engine;

	class Renderer
	{
	private:
		static bool						_glew_init;
		Engine							*_engine = nullptr;
		uint32_t						_width = 800;
		uint32_t						_height = 600;
		int32_t							_major_version = 3;
		int32_t							_minor_version = 3;
		uint32_t						_depth = 24;
		bool							_double_buffer = true;
		Scene							_scene;
		Camera							_cam;
		double							_last_ticks = 0;
		double							_diff_time = 0;

	public:
		explicit 		Renderer(Engine *engine) noexcept;
		virtual 		~Renderer() noexcept;

		inline uint32_t	width() const noexcept {
			return (this->_width);
		}

		inline uint32_t height() const noexcept {
			return (this->_height);
		}

		void			init() const noexcept;
		bool			renderFrame(GLFWwindow *win) noexcept;


		inline Scene	*scene() noexcept {
			return (&this->_scene);
		}
		inline Camera	*camera() noexcept {
			return (&this->_cam);
		}

		inline double		DiffSinceLastFrame() const noexcept {
			return (this->_diff_time);
		}
	};
}

#endif
