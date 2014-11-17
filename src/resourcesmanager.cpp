#include "resourcesmanager.h"
#include "mesh.h"
#include "parser3ds.h"

using Gema::ResourcesManager;
using Gema::Mesh;
using Gema::Parser3DS;

ResourcesManager 	ResourcesManager::_singleton;

ResourcesManager::~ResourcesManager()
{
	
}

bool	ResourcesManager::load() noexcept
{
	for (auto it : this->_files)
	{
		std::string &file = it;

		if (file.substr(file.length() - 4) == ".3ds")
		{
			Parser3DS parse;
			parse.load(file.c_str());
		}
	}
	return (true);
}