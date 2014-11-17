#ifndef GEMA_PARSER3DS_H
# define GEMA_PARSER3DS_H

# include "parser.h"
# include "mesh.h"
# include "material.h"
# include <iostream>

namespace Gema
{
	class Parser3DS : public Parser
	{
	private:
		uint16_t	_to_skip[1] { 2 };
		struct _chuck
		{
			uint16_t	id;
			uint32_t	len;
		} __attribute__((packed));

		char			*_buffer = nullptr;
		Mesh			*_current = nullptr;
		Material		*_current_material = nullptr;
		std::string		_material_name;

		std::string		_read_name(char *buffer) noexcept;

		inline _chuck	*_read_chuck(size_t index) noexcept {
			return ((_chuck*)(this->_buffer + index));
		}

		void			_parse_material_color(_chuck *c, int type) noexcept;
		void			_parse_material_specular(_chuck *c) noexcept;
		void			_parse_material_diffuse(_chuck *c) noexcept;
		void			_parse_material_ambient(_chuck *c) noexcept;
		void			_parse_material_name(_chuck *c) noexcept;
		void			_parse_material(_chuck *c) noexcept;
		void			_parse_face_material(_chuck *c) noexcept;
		void			_parse_face_list(_chuck *c) noexcept;
		void			_parse_vertex_list(_chuck *c) noexcept;
		void			_parse_triangular(_chuck *c) noexcept;
		void			_parse_object(_chuck *c) noexcept;
		void			_parse_editor(_chuck *c) noexcept;
		void			_parse_main(_chuck *c) noexcept;
		size_t			_parse_chuck(_chuck *chuck) noexcept;

	protected:
		virtual	bool	_raw_load(char *buffer, size_t len) noexcept;

	public:
		explicit 		Parser3DS() = default;
		virtual			~Parser3DS() noexcept = default;

		virtual bool	canParse(const std::string& file) noexcept;
	};
}

#endif