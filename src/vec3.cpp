#include "vec3.h"

using Gema::vec3;

vec3::vec3(const vec3& vec) noexcept
{
	this->_values[0] = vec._values[0];
	this->_values[1] = vec._values[1];
	this->_values[2] = vec._values[2];
}

vec3::vec3(float x, float y, float z) noexcept
{
	_values[0] = x;
	_values[1] = y;
	_values[2] = z;
}