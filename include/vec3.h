#ifndef GEMA_VEC3_H
# define GEMA_VEC3_H

# include <cmath>

namespace Gema
{
	class vec3
	{
	private:
		float	_values[3] = {0, 0, 0};

	public:
		explicit 	vec3() noexcept {};
		vec3(const vec3& vec) noexcept;
		explicit 	vec3(float x, float y, float z) noexcept;
		virtual 	~vec3() noexcept = default;

		inline float	x() const noexcept {
			return (this->_values[0]);
		}

		inline float	y() const noexcept {
			return (this->_values[1]);
		}

		inline float	z() const noexcept {
			return (this->_values[2]);
		}

		inline float&	x() noexcept {
			return (this->_values[0]);
		}

		inline float&	y() noexcept {
			return (this->_values[1]);
		}

		inline float&	z() noexcept {
			return (this->_values[2]);
		}

		inline double	magnitude() const noexcept {
			return (sqrt(this->_values[0] * this->_values[0] + this->_values[1] * this->_values[1] + this->_values[2] * this->_values[2]));
		}

		inline vec3 			normalize() const noexcept {
			double magn = this->magnitude();
			if (magn != 0)
				return vec3(this->_values[0] / magn, this->_values[1] / magn, this->_values[2] / magn);
			return (*this);
		}

		inline vec3				negate() const noexcept {
			return vec3(-this->_values[0], -this->_values[1], -this->_values[2]);
		}

		inline vec3				add(const vec3& vec) const noexcept {
			return vec3(this->_values[0] + vec._values[0], this->_values[1] + vec._values[1], this->_values[2] + vec._values[2]);
		}

		inline vec3 			mul(float n) const noexcept {
			return vec3(this->_values[0] * n, this->_values[1] * n, this->_values[2] * n);
		}

		inline double			dot(const vec3& vec) const noexcept {
			return (this->_values[0] * vec._values[0] + this->_values[1] * vec._values[1] + this->_values[2] * vec._values[2]);
		}

		static inline vec3 			cross(const vec3& v1, const vec3& v2) noexcept {
			return vec3(
				v1._values[1] * v2._values[2] - v1._values[2] * v2._values[1],
				v1._values[2] * v2._values[0] - v1._values[0] * v2._values[2],
				v1._values[0] * v2._values[1] - v1._values[1] * v2._values[0]
			);
		}

		inline const float			*values() const noexcept {
			return (this->_values);
		}
	};
}

#endif