#include "parser3ds.h"

using Gema::Parser3DS;
using Gema::vec3;
using Gema::Material;

std::string	Parser3DS::_read_name(char *buffer) noexcept
{
	int i = 0;
	for (;buffer[i];++i);
	return (std::string(buffer, i));
}

void	Parser3DS::_parse_material_color(_chuck *c, int type) noexcept
{
	if (type == 0)
		std::cout << "parse material ambient : current (" << (size_t)this->_current_material << ")" << std::endl;
	else if (type == 1)
		std::cout << "parse material diffuse : current (" << (size_t)this->_current_material << ")" << std::endl;
	else if (type == 2)
		std::cout << "parse material specular : current (" << (size_t)this->_current_material << ")" << std::endl;
	size_t 		index = (size_t)c - (size_t)this->_buffer;
	size_t 		i = sizeof(_chuck);
	
	while (i < c->len) {
		_chuck *child = this->_read_chuck(index + i);
		if (child->id == 0x11) {
			size_t i2 = sizeof(_chuck);
			uint8_t red = Parser::_read<uint8_t>(this->_buffer + index + i, i2);
			uint8_t green = Parser::_read<uint8_t>(this->_buffer + index + i, i2);
			uint8_t blue = Parser::_read<uint8_t>(this->_buffer + index + i, i2);
			std::cout << "\tRGB(" << (int)red << ", " << (int)green << ", " << (int)blue << ")" << std::endl;
			if (type == 0)
				this->_current_material->setAmbient(vec3((float)red / 255.0, (float)green / 255.0, (float)blue / 255.0));
			else if (type == 1)
				this->_current_material->setDiffuse(vec3((float)red / 255.0, (float)green / 255.0, (float)blue / 255.0));
			else
				this->_current_material->setSpecular(vec3((float)red / 255.0, (float)green / 255.0, (float)blue / 255.0));
		}
		i += child->len;
	}
}

void	Parser3DS::_parse_material_name(_chuck *c) noexcept
{
	std::cout << "parse material name : current (" << (size_t)this->_current_material << ")" << std::endl;
	size_t 		index = (size_t)c - (size_t)this->_buffer;
	size_t 		i = sizeof(_chuck);
	this->_material_name = this->_read_name(this->_buffer + index + i);
	std::cout << "\tname : " << this->_material_name << std::endl;
}

void	Parser3DS::_parse_material(_chuck *c) noexcept
{
	std::cout << "parse material" << std::endl;
	size_t 		index = (size_t)c - (size_t)this->_buffer;
	size_t 		i = sizeof(_chuck);
	this->_current_material = new Material();
	while (i < c->len) {
		_chuck *child = this->_read_chuck(index + i);
		if (child->id == 0xA000)
			this->_parse_material_name(child);
		else if (child->id == 0xa010)
			this->_parse_material_color(child, 0);
		else if (child->id == 0xA020)
			this->_parse_material_color(child, 1);
		else if (child->id == 0xA030)
			this->_parse_material_color(child, 2);
		else
			std::cout << "unknow parse : " << std::hex << child->id << std::dec << std::endl;
		i += child->len;
	}
	Material::registerMaterial(this->_material_name, this->_current_material);
	this->_current_material = nullptr;
}

void	Parser3DS::_parse_face_material(_chuck *c) noexcept
{
	std::cout << "parse face material : current (" << (size_t)this->_current << ")" << std::endl;
	size_t 		index = (size_t)c - (size_t)this->_buffer;
	size_t 		i = sizeof(_chuck);
	std::string name = this->_read_name(this->_buffer + index + i);
	std::cout << "\tname : " << name << std::endl;
	this->_current->setMaterialName(name);
}

void	Parser3DS::_parse_face_list(_chuck *c) noexcept
{
	std::cout << "parse face list : current (" << (size_t)this->_current << ")" << std::endl;
	size_t 		index = (size_t)c - (size_t)this->_buffer;
	size_t 		i = sizeof(_chuck);
	uint16_t	nb = Parser::_read<uint16_t>(this->_buffer + index, i);
	std::cout << "\tnb : " << nb << std::endl;
	std::vector<vec3>	new_vertices;
	for (uint16_t j = 0; j < nb; ++j) {
		uint16_t a = Parser::_read<uint16_t>(this->_buffer + index, i);
		uint16_t b = Parser::_read<uint16_t>(this->_buffer + index, i);
		uint16_t c = Parser::_read<uint16_t>(this->_buffer + index, i);
		uint16_t into = Parser::_read<uint16_t>(this->_buffer + index, i);
		(void)into;
		// std::cout << "\tFace (" << a << ", " << b << ", " << c << ") : into => " << into << std::endl;
		vec3 va = this->_current->vertices()[a];
		vec3 vb = this->_current->vertices()[b];
		vec3 vc = this->_current->vertices()[c];
		vec3 vab = vb.add(va.negate());
		vec3 vac = vc.add(va.negate());
		vec3 normal = vec3::cross(vab, vac);
		this->_current->indices().push_back(a);
		new_vertices.push_back(this->_current->vertices()[a]);
		this->_current->normals().push_back(normal.normalize());
		new_vertices.push_back(this->_current->vertices()[b]);
		this->_current->normals().push_back(normal.normalize());
		new_vertices.push_back(this->_current->vertices()[c]);
		this->_current->normals().push_back(normal.normalize());
		this->_current->indices().push_back(b);
		this->_current->indices().push_back(c);
	}
	this->_current->vertices() = new_vertices;
	while (i < c->len) {
		_chuck *child = this->_read_chuck(index + i);
		if (child->id == 0x4130)
			this->_parse_face_material(child);
		else
			std::cout << "unknow parse : " << std::hex << child->id << std::dec << std::endl;
		i += child->len;
	}
}

void	Parser3DS::_parse_vertex_list(_chuck *c) noexcept
{
	std::cout << "parse vertex list : current (" << (size_t)this->_current << ")" << std::endl;
	size_t 		index = (size_t)c - (size_t)this->_buffer;
	size_t 		i = sizeof(_chuck);
	uint16_t	nb = Parser::_read<uint16_t>(this->_buffer + index, i);
	std::cout << "\tnb : " << nb << std::endl;
	for (uint16_t j = 0; j < nb; ++j) {
		float x = Parser::_read<float>(this->_buffer + index, i);
		float y = Parser::_read<float>(this->_buffer + index, i);
		float z = Parser::_read<float>(this->_buffer + index, i);
		// std::cout << "\tVertex (" << x << ", " << y << ", " << z << ")" << std::endl;
		this->_current->vertices().push_back(vec3(x, y, z));
	}
}

void	Parser3DS::_parse_triangular(_chuck *c) noexcept
{
	std::cout << "parse triangular : current (" << (size_t)this->_current << ")" << std::endl;
	size_t index = (size_t)c - (size_t)this->_buffer;
	size_t i = sizeof(_chuck);
	while (i < c->len) {
		_chuck *child = this->_read_chuck(index + i);
		if (child->id == 0x4110)
			this->_parse_vertex_list(child);
		else if (child->id == 0x4120)
			this->_parse_face_list(child);
		else
			std::cout << "unknow parse : " << std::hex << child->id << std::dec << std::endl;
		i += child->len;
	}
}

void	Parser3DS::_parse_object(_chuck *c) noexcept
{
	std::cout << "parse object" << std::endl;
	size_t index = (size_t)c - (size_t)this->_buffer;
	size_t i = sizeof(_chuck);
	std::string name = this->_read_name(this->_buffer + index + i);
	i += name.length() + 1;
	std::cout << "\tname : " << name << std::endl;
	this->_current = new Mesh();
	while (i < c->len) {
		_chuck *child = this->_read_chuck(index + i);
		if (child->id == 0x4100)
			this->_parse_triangular(child);
		i += child->len;
	}
	Mesh::registerMesh(name, this->_current);
	this->_current = nullptr;
}

void	Parser3DS::_parse_editor(_chuck *c) noexcept
{
	std::cout << "parse editor" << std::endl;
	size_t index = (size_t)c - (size_t)this->_buffer;
	size_t i = sizeof(_chuck);
	while (i < c->len) {
		_chuck *child = this->_read_chuck(index + i);
		if (child->id == 0x4000)
			this->_parse_object(child);
		else if (child->id == 0xAFFF)
			this->_parse_material(child);
		i += child->len;
	}
}

void	Parser3DS::_parse_main(_chuck *c) noexcept
{
	std::cout << "parse main" << std::endl;
	size_t index = (size_t)c - (size_t)this->_buffer;
	size_t i = sizeof(_chuck);
	while (i < c->len) {
		_chuck *child = this->_read_chuck(index + i);
		if (child->id == 0x3D3D)
			this->_parse_editor(child);
		i += child->len;
	}
}

size_t	Parser3DS::_parse_chuck(_chuck *c) noexcept
{
	if (c->id == 0x4D4D)
		this->_parse_main(c);
	return (c->len);
}

bool	Parser3DS::_raw_load(char *buffer, size_t len) noexcept
{
	size_t	index = 0;

	this->_buffer = buffer;
	while (index < len)
		index += this->_parse_chuck(this->_read_chuck(index));
	delete [] buffer;
	return (true);
}

bool	Parser3DS::canParse(const std::string& file) noexcept
{
	if (!file.substr(file.length() - 4).compare(".3ds"))
		return (true);
	return (false);
}