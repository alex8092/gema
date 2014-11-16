#include "resourcesmanager.h"
#include "mesh.h"

using Gema::ResourcesManager;
using Gema::Mesh;

ResourcesManager 	ResourcesManager::_singleton;

ResourcesManager::~ResourcesManager()
{
	
}

bool	ResourcesManager::load() noexcept
{
	for (auto it : this->_files)
	{
		std::string &str = it;

		if (str.substr(str.length() - 4) == ".obj")
		{
			// std::string 	line;
			// std::ifstream	ifs(str.c_str());
			// Mesh 			*m = nullptr;
			// while (std::getline(ifs, line))
			// {
			// 	if (line[0] == 'o')
			// 	{
			// 		m = new Mesh();
			// 		m->setDrawType(GL_TRIANGLE_STRIP);
			// 		std::cout << "name : " << line.substr(2) << std::endl;
			// 		Mesh::registerMesh(line.substr(2), m);
			// 	}
			// 	else if (line[0] == 'v')
			// 	{
			// 		if (m)
			// 		{
			// 			vec3 vec;
			// 			std::stringstream ss(line.substr(2));
			// 			std::string tmp;
			// 			if (ss >> tmp)
			// 			{
			// 				std::stringstream xpos(tmp);
			// 				xpos >> vec.x();
			// 			}
			// 			if (ss >> tmp)
			// 			{
			// 				std::stringstream xpos(tmp);
			// 				xpos >> vec.y();
			// 			}
			// 			if (ss >> tmp)
			// 			{
			// 				std::stringstream xpos(tmp);
			// 				xpos >> vec.z();
			// 			}
			// 			std::cout << "vec : (" << vec.x() << ", " << vec.y() << ", " << vec.z() << ")" << std::endl;
			// 			m->vertices().push_back(vec);
			// 		}
			// 	}
			// 	else if (line[0] == 'f')
			// 	{
			// 		if (m)
			// 		{
			// 			std::stringstream ss(line.substr(2));
			// 			std::string tmp;
			// 			std::cout << "face : ";
			// 			int i = 0;
			// 			uint32_t sav1 = 0;
			// 			uint32_t sav2 = 0;
			// 			while (ss >> tmp)
			// 			{
			// 				uint32_t value;
			// 				std::stringstream val(tmp);
			// 				val >> value;
			// 				std::cout << value << " - ";
			// 				if (i == 2)
			// 					sav1 = value;
			// 				else if (i == 1)
			// 					sav2 = value;
			// 				else if (i == 3)
			// 				{
			// 					m->indices().push_back(sav1);
			// 					m->indices().push_back(sav2);
			// 				}
			// 				m->indices().push_back(value);
			// 				++i;
			// 			}
			// 			std::cout << std::endl;
			// 		}
			// 	}
			// 	std::cout << line << std::endl;
			// }
		}
		else if (str.substr(str.length() - 4) == ".3ds")
		{
			std::ifstream ifs(str.c_str(), std::ios::binary);
			ifs.seekg(0, ifs.end);
			int len = ifs.tellg();
			ifs.seekg(0, ifs.beg);
			char *buffer = new char[len];
			ifs.read(buffer, len);
			struct chuck {
				uint16_t id;
				uint32_t size;
			} __attribute__((packed));
			chuck *c = (chuck*)buffer;
			int index = 0;
			while (index < len)
			{
				int saveIndex = index;
				c = ResourcesManager::_read_struct<chuck>(buffer, index);
				int size = c->size;
				std::cout << "#Chuck" << std::endl;
				std::cout << "\tid : " << std::hex << c->id << std::dec << std::endl;
				std::cout << "\tsize : " << c->size << std::endl;
				chuck *c2 = ResourcesManager::_read_struct<chuck>(buffer, index);
				std::cout << "\t#Chuck" << std::endl;
				std::cout << "\t\tid : " << std::hex << c2->id << std::dec << std::endl;
				std::cout << "\t\tsize : " << c2->size << std::endl;
				index += c2->size - sizeof(chuck);
				chuck *c3 = ResourcesManager::_read_struct<chuck>(buffer, index);
				std::cout << "\t#Chuck" << std::endl;
				std::cout << "\t\tid : " << std::hex << c3->id << std::dec << std::endl;
				std::cout << "\t\tsize : " << c3->size << std::endl;
				chuck *c4 = ResourcesManager::_read_struct<chuck>(buffer, index);
				std::cout << "\t\t#Chuck" << std::endl;
				std::cout << "\t\t\tid : " << std::hex << c4->id << std::dec << std::endl;
				std::cout << "\t\t\tsize : " << c4->size << std::endl;
				index += c4->size - sizeof(chuck);
				chuck *c5 = ResourcesManager::_read_struct<chuck>(buffer, index);
				std::cout << "\t\t#Chuck" << std::endl;
				std::cout << "\t\t\tid : " << std::hex << c5->id << std::dec << std::endl;
				std::cout << "\t\t\tsize : " << c5->size << std::endl;
				int i = index;
				for (; i < len; ++i) {
					if (buffer[i] == 0)
						break ;
				}
				std::string name(buffer + index, i - index);
				Mesh *m = new Mesh();
				std::cout << "name : \"" << name << "\"" << std::endl;
				Mesh::registerMesh(name, m);
				std::cout << "\t\t\tobject name : " << name << std::endl;
				index = i + 1;
				chuck *c6 = ResourcesManager::_read_struct<chuck>(buffer, index);
				std::cout << "\t\t\t#Chuck" << std::endl;
				std::cout << "\t\t\t\tid : " << std::hex << c6->id << std::dec << std::endl;
				std::cout << "\t\t\t\tsize : " << c6->size << std::endl;
				chuck *c7 = ResourcesManager::_read_struct<chuck>(buffer, index);
				std::cout << "\t\t\t\t#Chuck" << std::endl;
				std::cout << "\t\t\t\t\tid : " << std::hex << c7->id << std::dec << std::endl;
				std::cout << "\t\t\t\t\tsize : " << c7->size << std::endl;
				uint16_t nbVertices = ResourcesManager::_read<uint16_t>(buffer, index);
				std::cout << "\t\t\t\t\t\tnb vertices : " << nbVertices << std::endl;
				for (uint16_t j = 0; j < nbVertices; ++j)
				{
					float	x = ResourcesManager::_read<float>(buffer, index);
					float	y = ResourcesManager::_read<float>(buffer, index);
					float	z = ResourcesManager::_read<float>(buffer, index);
					m->vertices().push_back(vec3(x, y, z));
					std::cout << "\t\t\t\t\t\tV (" << x << ", " << y << ", " << z << ")" << std::endl;
				}
				chuck *c8 = ResourcesManager::_read_struct<chuck>(buffer, index);
				std::cout << "\t\t\t\t#Chuck" << std::endl;
				std::cout << "\t\t\t\t\tid : " << std::hex << c8->id << std::dec << std::endl;
				std::cout << "\t\t\t\t\tsize : " << c8->size << std::endl;
				uint16_t nbPolygon = ResourcesManager::_read<uint16_t>(buffer, index);
				std::cout << "\t\t\t\t\t\tnb poly : " << nbPolygon << std::endl;
				for (uint16_t j = 0; j < nbPolygon; ++j)
				{
					uint16_t vA = ResourcesManager::_read<uint16_t>(buffer, index);
					uint16_t vB = ResourcesManager::_read<uint16_t>(buffer, index);
					uint16_t vC = ResourcesManager::_read<uint16_t>(buffer, index);
					m->indices().push_back(vA);
					m->indices().push_back(vB);
					m->indices().push_back(vC);
					uint16_t faceInto = ResourcesManager::_read<uint16_t>(buffer, index);
					std::cout << "\t\t\t\t\t\tF (" << vA << ", " << vB << ", " << vC << ") - into : " << faceInto << std::endl;
				}
				
				break ;
				index =  saveIndex + size;
			}
			delete [] buffer;
		}
	}
	return (true);
}