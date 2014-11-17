#ifndef GEMA_MATERIAL_H
# define GEMA_MATERIAL_H

# include "vec3.h"
# include <string>
# include <map>

namespace Gema
{
	class Material
	{
	private:
		static std::map<std::string, Material*>	_materials;

		vec3									_ambient = vec3(1.0, 1.0, 1.0);
		vec3									_diffuse = vec3(1.0, 1.0, 1.0);
		vec3									_specular = vec3(1.0, 1.0, 1.0);

	public:
		explicit 				Material() = default;
		virtual					~Material() noexcept = default;

		static inline bool		registerMaterial(const std::string& name, Material *mat) noexcept {
			auto it = Material::_materials.find(name);
			if (it != Material::_materials.end())
				return (false);
			Material::_materials[name] = mat;
			return (true);
		}

		static inline Material 	*get(const std::string& name) noexcept {
			auto it = Material::_materials.find(name);
			if (it != Material::_materials.end())
				return (it->second);
			return (nullptr);
		}

		inline void				setAmbient(const vec3& color) noexcept {
			this->_ambient = color;
		}
		inline void 			setDiffuse(const vec3& color) noexcept {
			this->_diffuse = color;
		}
		inline void				setSpecular(const vec3& color) noexcept {
			this->_specular = color;
		}

		inline const vec3&			ambient() const noexcept {
			return (this->_ambient);
		}
		inline const vec3&			diffuse() const noexcept {
			return (this->_diffuse);
		}
		inline const vec3&			specular() const noexcept {
			return (this->_specular);
		}
	};
}

#endif