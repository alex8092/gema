#include "parser.h"

using Gema::Parser;
using Gema::vec3;

bool	Parser::load(const std::string& file) noexcept
{
	std::ifstream	ifs(file.c_str(), std::ios::binary);
	if (!ifs)
		return (false);
	ifs.seekg(0, ifs.end);
	size_t len = ifs.tellg();
	ifs.seekg(0, ifs.beg);
	char	*buffer = new char[len];
	ifs.read(buffer, len);
	ifs.close();
	return (this->_raw_load(buffer, len));
}