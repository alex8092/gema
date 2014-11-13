#ifndef GEMA_MAT4_H
# define GEMA_MAT4_H

# include "vec3.h"

namespace Gema
{
	class mat4
	{
	private:
		float	_values[16];

	public:
		explicit 					mat4() noexcept;
		explicit 					mat4(float *array) noexcept;
		explicit 					mat4(const mat4& mat) noexcept;
		virtual						~mat4() noexcept = default;

		mat4 						&operator=(const mat4& mat) noexcept;

		mat4						&identity() noexcept;
		mat4						&frustum(float left, float right, float bottom, float top, float near, float far) noexcept;
		mat4						&perspective(float fovy, float aspect, float near, float far) noexcept;
		mat4						&translate(float x, float y, float z) noexcept;
		mat4						&lookAt(const vec3& pos, const vec3& target, const vec3& up);
		mat4						&operator*=(const mat4& mat) noexcept;

		inline mat4 				&translate(const vec3& vec) noexcept {
			return (this->translate(vec.x(), vec.y(), vec.z()));
		}

		mat4 						&rotate(const vec3& axis, float theta) noexcept;
		mat4						&scale(const vec3& datas) noexcept;

		inline const float	* const values() const noexcept {
			return (this->_values);
		}
		inline float&				operator[](int index) noexcept {
			return (this->_values[index]);
		}

	};
}

#endif