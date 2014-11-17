#include "resourcesmanager.h"
#include "mesh.h"
#include "parser3ds.h"
#include "parserobj.h"

using Gema::ResourcesManager;
using Gema::Mesh;
using Gema::Parser3DS;
using Gema::ParserOBJ;

ResourcesManager 	ResourcesManager::_singleton;

ResourcesManager::~ResourcesManager()
{
	
}

bool	ResourcesManager::load() noexcept
{
	for (auto it : this->_files)
	{
		std::string &file = it;
		ParserOBJ parseobj;
		Parser3DS parse3ds;
		if (parseobj.canParse(file))
			parseobj.load(file);
		else if (parse3ds.canParse(file))
			parse3ds.load(file);
	}
	return (true);
}