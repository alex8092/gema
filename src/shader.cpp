#include "shader.h"

using Gema::Shader;

Shader::Shader(const std::string& vertex, const std::string& fragment) :
	_vertex_source(vertex),
	_fragment_source(fragment)
{

}

void	Shader::unload() noexcept
{
	if (glIsShader(this->_vertex_id) == GL_TRUE) {
		glDeleteShader(this->_vertex_id);
		this->_vertex_id = 0;
	}
	if (glIsShader(this->_fragment_id) == GL_TRUE) {
		glDeleteShader(this->_fragment_id);
		this->_fragment_id = 0;
	}
	if (glIsProgram(this->_program_id) == GL_TRUE) {
		glDeleteProgram(this->_program_id);
		this->_program_id = 0;
	}
	this->_is_load = false;
}

char 	*Shader::_get_error(GLuint &shader, GLenum type, bool isProgram) noexcept
{
	GLint 	errorNumber;
	GLint 	errorLength;
	char 	*errorStr = nullptr;

	if (!isProgram)
		glGetShaderiv(shader, type, &errorNumber);
	else
		glGetProgramiv(shader, type, &errorNumber);
	if (errorNumber != GL_TRUE)
	{
		if (!isProgram)
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &errorLength);
		else
			glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &errorLength);
		errorStr = new char[errorLength + 1];
		glGetShaderInfoLog(shader, errorLength, &errorLength, errorStr);
		errorStr[errorLength] = 0;
	}
	return (errorStr);
}

bool	Shader::_compile(GLuint &shader, GLenum type, const std::string& source) noexcept
{
	std::stringstream 	stream;
	std::string 		tmp;
	std::ifstream		src(source.c_str());
	const GLchar		*csource = nullptr;
	char				*error = nullptr;

	shader = glCreateShader(type);
	if (!shader) {
		std::cerr << "Type of shader does not exist(" << type << ")" << std::endl;
		return (false);
	}

	if (!src) {
		std::cerr << "File \"" << source << "\" not found" << std::endl;
		glDeleteShader(shader);
		shader = 0;
		return (false);
	}

	while (std::getline(src, tmp))
		stream << tmp << '\n';
	src.close();
	tmp = stream.str();
	csource = (const GLchar *)tmp.c_str();
	glShaderSource(shader, 1, &csource, 0);
	glCompileShader(shader);
	if ((error = Shader::_get_error(shader, GL_COMPILE_STATUS))) {
		std::cerr << "Compilation error [" << source << "] : " << error << std::endl;
		delete [] error;
		glDeleteShader(shader);
		shader = 0;
		return (false);
	}
	return (true);
}

bool	Shader::load() noexcept
{
	char	*error = nullptr;

	this->unload();
	if (!Shader::_compile(this->_vertex_id, GL_VERTEX_SHADER, this->_vertex_source))
		return (false);
	if (!Shader::_compile(this->_fragment_id, GL_FRAGMENT_SHADER, this->_fragment_source))
	{
		this->unload();
		return (false);
	}
	this->_program_id = glCreateProgram();
	glAttachShader(this->_program_id, this->_vertex_id);
	glAttachShader(this->_program_id, this->_fragment_id);
	for (auto it : this->_bind_locations)
		glBindAttribLocation(this->_program_id, it.second, it.first.c_str());
	glLinkProgram(this->_program_id);
	if ((error = Shader::_get_error(this->_program_id, GL_LINK_STATUS, true))) {
		std::cerr << "Cannot link shader program : " << error << std::endl;
		delete [] error;
		this->unload();
		return (false);
	}
	this->_is_load = true;
	return (true);
}