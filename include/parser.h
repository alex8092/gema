#ifndef GEMA_PARSER_H
# define GEMA_PARSER_H

# include "vec3.h"
# include <vector>
# include <sstream>
# include <fstream>
# include <cstdint>

namespace Gema
{
	class Parser
	{
	protected:
		std::vector<vec3>		_vertices;
		std::vector<uint32_t>	_indices;
		std::vector<vec3>		_normals;

		template <class T, class Tmp = T>
		static T	_read(char *buffer, size_t& index) noexcept {
			index += sizeof(T);
			return ((T)*(Tmp*)(buffer + index - sizeof(T)));
		}

		virtual	bool			_raw_load(char *buffer, size_t len) noexcept = 0;

	public:
		explicit 							Parser() = default;
		virtual								~Parser() noexcept = default;

		bool								load(const std::string& file) noexcept;
		virtual bool						canParse(const std::string& file) noexcept = 0;
		
		inline const std::vector<uint32_t>&	indices() const noexcept {
			return (this->_indices);
		}

		inline const std::vector<vec3>&		vertices() const noexcept {
			return (this->_vertices);
		}

		inline const std::vector<vec3>&		normals() const noexcept {
			return (this->_normals);
		}
	};
}

#endif