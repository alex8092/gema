#ifndef GEMA_RENDERER_H
# define GEMA_RENDERER_H

# include <stdint.h>
# include <GL/glew.h>

# define GL3_PROTOTYPES 1

# ifdef __APPLE__
#  include <OpenGL/gl.h>
# else
#  include <GL/gl.h>
# endif

# include "scene.h"
# include "camera.h"
# include "mat4.h"

namespace Gema
{
	class Renderer
	{
	private:
		static bool						_glew_init;
		uint32_t						_width = 800;
		uint32_t						_height = 600;
		uint32_t						_depth = 24;
		bool							_double_buffer = true;
		Scene							_scene;
		Camera							_cam;
		double							_last_ticks = 0;
		double							_diff_time = 0;
		static Renderer 				_singleton;
		mat4							_proj;
		mat4							_view;
		mat4							_world;
		explicit 						Renderer() noexcept;

	public:
		virtual 						~Renderer() noexcept;
		bool							render(void) noexcept;

		static inline Renderer 			*singleton() noexcept {
			return (&Renderer::_singleton);
		}

		inline uint32_t					width() const noexcept {
			return (this->_width);
		}

		inline uint32_t 				height() const noexcept {
			return (this->_height);
		}

		inline Scene					*scene() noexcept {
			return (&this->_scene);
		}
		inline Camera					*camera() noexcept {
			return (&this->_cam);
		}

		inline mat4&					projMatrix() noexcept {
			return (this->_proj);
		}

		inline mat4&					viewMatrix() noexcept {
			return (this->_view);
		}

		inline mat4&					worldMatrix() noexcept {
			return (this->_world);
		}

		inline double					DiffSinceLastFrame() const noexcept {
			return (this->_diff_time);
		}
	};
}

#endif
