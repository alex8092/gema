#ifndef GEMA_SHADER_H
# define GEMA_SHADER_H

# include <GL/glew.h>
# define GL3_PROTOTYPES 1
# include <GL/gl.h>
# include <string>
# include <map>
# include <sstream>
# include <fstream>
# include <iostream>

namespace Gema
{
	class Shader
	{
	private:
		GLuint							_program_id = 0;
		GLuint							_vertex_id = 0;
		GLuint							_fragment_id = 0;
		std::string						_vertex_source;
		std::string						_fragment_source;
		bool							_is_load = false;
		std::map<std::string, uint8_t>	_bind_locations;
		std::map<std::string, GLint>	_uniform_locations;

		static char		*_get_error(GLuint &shader, GLenum type, bool isProgram = false) noexcept;
		static bool		_compile(GLuint &shader, GLenum type, const std::string& source) noexcept;

	public:
		explicit		Shader(const std::string& vertex, const std::string& fragment);
		virtual			~Shader() noexcept = default;

		bool			load() noexcept;
		void			unload() noexcept;

		inline void		setLocation(uint8_t location, const std::string& name) noexcept {
			this->_bind_locations[name] = location;
		}

		inline uint8_t	location(const std::string& name) const {
			auto it = this->_bind_locations.find(name);
			if (it != this->_bind_locations.end())
				return (it->second);
			throw "Unable to find location";
		}

		inline GLint 	uniformLocation(const std::string& name) noexcept {
			auto it = this->_uniform_locations.find(name);
			if (it != this->_uniform_locations.end())
				return (it->second);
			GLint loc = glGetUniformLocation(this->_program_id, name.c_str());
			this->_uniform_locations[name] = loc;
			return (loc);
		}

		inline bool		isLoad() const noexcept {
			return (this->_is_load);
		}

		inline GLuint	id() const noexcept {
			return (this->_program_id);
		}
	};
}

#endif