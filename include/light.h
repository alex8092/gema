#ifndef GEMA_LIGHT_H
# define GEMA_LIGHT_H

# include "vec3.h"

namespace Gema
{
	enum class LightType { POINT, SPOT, DIRECTIONAL };
	class Light
	{
	private:
		LightType	_type = LightType::POINT;
		vec3		_ambient = vec3(1.0, 1.0, 1.0);
		vec3		_diffuse = vec3(1.0, 1.0, 1.0);
		vec3		_specular = vec3(1.0, 1.0, 1.0);
		vec3		_pos;

	public:
		explicit	Light() = default;
		virtual		~Light() noexcept = default;

		inline void	setType(LightType type) noexcept {
			this->_type = type;
		}

		inline void setPosition(const vec3& pos) noexcept {
			this->_pos = pos;
		}

		inline void setAmbient(const vec3& color) noexcept {
			this->_ambient = color;
		}

		inline void setDiffuse(const vec3& color) noexcept {
			this->_diffuse = color;
		}

		inline void setSpecular(const vec3& color) noexcept {
			this->_specular = color;
		}

		inline const vec3& pos() const noexcept {
			return (this->_pos);
		}

		inline const vec3& ambient() const noexcept {
			return (this->_ambient);
		}

		inline const vec3& diffuse() const noexcept {
			return (this->_diffuse);
		}

		inline const vec3& specular() const noexcept {
			return (this->_specular);
		}

	};
}

#endif