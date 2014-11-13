#include "vec3.h"

using Gema::vec3;

vec3::vec3(const vec3& vec) noexcept
{
	this->_x = vec._x;
	this->_y = vec._y;
	this->_z = vec._z;
}

vec3::vec3(float x, float y, float z) noexcept :
	_x(x),
	_y(y),
	_z(z)
{

}