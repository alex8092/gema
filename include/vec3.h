#ifndef GEMA_VEC3_H
# define GEMA_VEC3_H

# include <cmath>

namespace Gema
{
	class vec3
	{
	private:
		float	_x = 0;
		float	_y = 0;
		float	_z = 0;

	public:
		explicit 	vec3() noexcept {};
		vec3(const vec3& vec) noexcept;
		explicit 	vec3(float x, float y, float z) noexcept;
		virtual 	~vec3() noexcept = default;

		inline float	x() const noexcept {
			return (this->_x);
		}

		inline float	y() const noexcept {
			return (this->_y);
		}

		inline float	z() const noexcept {
			return (this->_z);
		}

		inline double	magnitude() const noexcept {
			return (sqrt(this->_x * this->_x + this->_y * this->_y + this->_z * this->_z));
		}

		inline vec3 			normalize() const noexcept {
			double magn = this->magnitude();
			if (magn != 0)
				return vec3(this->_x / magn, this->_y / magn, this->_z / magn);
			return (*this);
		}

		inline vec3				negate() const noexcept {
			return vec3(-this->_x, -this->_y, -this->_z);
		}

		inline vec3				add(const vec3& vec) const noexcept {
			return vec3(this->_x + vec._x, this->_y + vec._y, this->_z + vec._z);
		}

		inline double			dot(const vec3& vec) const noexcept {
			return (this->_x * vec._x + this->_y * vec._y + this->_z * vec._z);
		}

		static inline vec3 			cross(const vec3& v1, const vec3& v2) noexcept {
			return vec3(
				v1._y * v2._z - v1._z * v2._y,
				v1._z * v2._x - v1._x * v2._z,
				v1._x * v2._y - v1._y * v2._x
			);
		}
	};
}

#endif