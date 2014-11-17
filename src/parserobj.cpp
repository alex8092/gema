#include "parserobj.h"

using Gema::ParserOBJ;
using Gema::Mesh;
using Gema::vec3;

bool	ParserOBJ::_raw_load(char *buffer, size_t len) noexcept
{
//	size_t	index = 0;
	(void)len;

	this->_buffer = buffer;
	std::stringstream ss(this->_buffer);
	std::string line;
	std::string name;
	std::string nameMaterial;
	std::vector<vec3>	vertices;
	std::vector<vec3>	normales;
	while (std::getline(ss, line))
	{
		if (line[0] == 'o')
		{
			if (this->_current)
			{
				Mesh::registerMesh(name, this->_current);
			}
			name = line.substr(2);
			std::cout << "parse object : " << name << std::endl;
			this->_current = new Mesh();
		}
		else if (line[0] == 'v' && line[1] == ' ')
		{
			std::stringstream coord(line.substr(2));
			vec3 vec;
			for (int i = 0; i < 3; ++i)
			{
				if (i == 0)
					coord >> vec.x();
				else if (i == 1)
					coord >> vec.y();
				else
					coord >> vec.z();
			}
			// std::cout << "Vertex : (" << vec.x() << ", " << vec.y() << ", " << vec.z() << ")" << std::endl;
			vertices.push_back(vec);
		}
		else if (line[0] == 'v' && line[1] == 'n')
		{
			std::stringstream coord(line.substr(3));
			vec3 vec;
			for (int i = 0; i < 3; ++i)
			{
				if (i == 0)
					coord >> vec.x();
				else if (i == 1)
					coord >> vec.y();
				else
					coord >> vec.z();
			}
			// std::cout << "Normale : (" << vec.x() << ", " << vec.y() << ", " << vec.z() << ")" << std::endl;
			normales.push_back(vec);
		}
		else if (line[0] == 'f')
		{
			std::stringstream desc(line.substr(2));
			std::string descStr;
			for (int i = 0; i < 3; ++i)
			{
				desc >> descStr;
				std::stringstream desc2(descStr);
				std::string tmp;
				for (int j = 0; j < 3; ++j)
				{
					std::getline(desc2, tmp, '/');
					std::stringstream convert(tmp);
					uint32_t value;
					convert >> value;
					--value;
					if (j == 0)
					{
						// std::cout << "Vertex (" << vertices[value].x() << ", " << vertices[value].y() << ", " << vertices[value].z() << ")" << std::endl;
						this->_current->vertices().push_back(vertices[value]);
					}
					else if (j == 2)
					{
						// std::cout << "Normal (" << normales[value].x() << ", " << normales[value].y() << ", " << normales[value].z() << ")" << std::endl;
						this->_current->normals().push_back(normales[value]);
					}
				}
			}
		}
		else if (line.substr(0, 7) == "usemtl ")
		{
			this->_current->setMaterialName(line.substr(7));
			std::cout << "use material : " << line.substr(7) << std::endl;
		}
		else if (line.substr(0, 7) == "newmtl ")
		{
			if (this->_current_material)
				Material::registerMaterial(nameMaterial, this->_current_material);
			nameMaterial = line.substr(7);
			this->_current_material = new Material();
			std::cout << "new material : " << nameMaterial << std::endl;
		}
		else if (line.substr(0, 3) == "Ka ")
		{
			std::stringstream coord(line.substr(2));
			vec3 vec;
			for (int i = 0; i < 3; ++i)
			{
				if (i == 0)
					coord >> vec.x();
				else if (i == 1)
					coord >> vec.y();
				else
					coord >> vec.z();
			}
			this->_current_material->setAmbient(vec);
		}
		else if (line.substr(0, 3) == "Ks ")
		{
			std::stringstream coord(line.substr(2));
			vec3 vec;
			for (int i = 0; i < 3; ++i)
			{
				if (i == 0)
					coord >> vec.x();
				else if (i == 1)
					coord >> vec.y();
				else
					coord >> vec.z();
			}
			this->_current_material->setSpecular(vec);
		}
		else if (line.substr(0, 3) == "Kd ")
		{
			std::stringstream coord(line.substr(2));
			vec3 vec;
			for (int i = 0; i < 3; ++i)
			{
				if (i == 0)
					coord >> vec.x();
				else if (i == 1)
					coord >> vec.y();
				else
					coord >> vec.z();
			}
			this->_current_material->setDiffuse(vec);
		}
	}
	if (this->_current_material)
				Material::registerMaterial(nameMaterial, this->_current_material);
	if (this->_current)
		Mesh::registerMesh(name, this->_current);
	delete [] buffer;
	return (true);
}

bool	ParserOBJ::canParse(const std::string& file) noexcept
{
	if (!file.substr(file.length() - 4).compare(".obj"))
		return (true);
	else if (!file.substr(file.length() - 4).compare(".mtl"))
		return (true);
	return (false);
}
