#ifndef GEMA_MESH_H
# define GEMA_MESH_H

# include <string>
# include <map>
# include <vector>
# include <stdint.h>
# include <list>
# include "vec3.h"
# include "material.h"
# include "shader.h"
# include <GL/glew.h>
# define GL3_PROTOTYPES 1
# ifdef __APPLE__
#  include <OpenGL/gl.h>
# else
#  include <GL/gl.h>
# endif

namespace Gema
{
	class Mesh
	{
	private:
		static std::map<std::string, Mesh*>	_register_meshs;
		std::vector<vec3>					_vertices;
		std::vector<uint32_t>				_indices;
		std::vector<vec3>					_normals;
		bool								_is_build = false;
		GLuint								_vbo[3];
		GLenum								_draw_type = GL_TRIANGLES;
		Material 							*_material;
		std::string							_material_name;
		Shader								*_shader;

	public:
		explicit 					Mesh() = default;
		virtual						~Mesh() noexcept = default;

		static inline void			registerMesh(const std::string& name, Mesh *mesh) noexcept {
			if (!Mesh::isRegister(name))
				Mesh::_register_meshs[name] = mesh;
		}
		static inline bool			isRegister(const std::string& name) noexcept {
			auto it = Mesh::_register_meshs.find(name);
			if (it != Mesh::_register_meshs.end())
				return (true);
			return (false);
		}

		static inline Mesh 			*get(const std::string& name) {
			return (Mesh::_register_meshs[name]);
		}

		inline std::vector<vec3>&	vertices() noexcept {
			return (this->_vertices);
		}
		inline std::vector<uint32_t>& indices() noexcept {
			return (this->_indices);
		}
		inline std::vector<vec3>&	normals() noexcept {
			return (this->_normals);
		}
		inline void						setMaterialName(const std::string& name) noexcept {
			this->_material_name = name;
			if (this->_material != nullptr)
				this->_material = nullptr;
		}
		inline void						setDrawType(GLenum type) noexcept {
			this->_draw_type = type;
		}

		virtual bool					draw() noexcept;
	};
}

#endif
