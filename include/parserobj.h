#ifndef GEMA_PARSEROBJ_H
# define GEMA_PARSEROBJ_H

# include "parser.h"
# include "mesh.h"
# include "vec3.h"
# include "material.h"
# include <iostream>
# include <sstream>

namespace Gema
{
	class ParserOBJ : public Parser
	{
	private:
		char				*_buffer = nullptr;
		Mesh				*_current = nullptr;
		Material			*_current_material = nullptr;

	protected:
		virtual	bool	_raw_load(char *buffer, size_t len) noexcept;

	public:
		explicit 		ParserOBJ() = default;
		virtual			~ParserOBJ() noexcept = default;

		virtual bool	canParse(const std::string& file) noexcept;
	};
}

#endif