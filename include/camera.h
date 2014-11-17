#ifndef GEMA_CAMERA_H
# define GEMA_CAMERA_H

# include "vec3.h"
# include "input.h"

namespace Gema
{
	class Camera : public InputListener
	{
	private:
		float	_phi = 0.0;
		float	_theta = 0.0;
		vec3	_move = vec3(0, 0, 0);
		vec3	_forward;
		vec3	_up = vec3(0, 1, 0);
		vec3	_left;
		vec3	_pos = vec3(3, 0, 3);
		vec3	_look = vec3(0, 0, 0);
		float	_speed = 0.1f;
		float	_sensitivity = 0.3f;

	public:
		explicit			Camera() noexcept = default;
		virtual				~Camera() noexcept = default;

		void				update() noexcept;

		inline const vec3&	position() const noexcept {
			return (this->_pos);
		}

		inline const vec3&	target() const noexcept {
			return (this->_look);
		}

		inline const vec3&	up() const noexcept {
			return (this->_up);
		}

		virtual void 	onMouseMove(int16_t xRel, int16_t yRel) noexcept;
		virtual void 	onMousePressed(uint8_t button) noexcept;
		virtual void 	onMouseReleased(uint8_t button) noexcept;
		virtual bool 	onKeyPressed(int code) noexcept;
		virtual bool 	onKeyReleased(int code) noexcept;
	};
}

#endif