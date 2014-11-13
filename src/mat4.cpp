#include "mat4.h"
#include <cmath>

using Gema::mat4;

mat4::mat4() noexcept
{
	this->identity();
}

mat4::mat4(float *array) noexcept
{
	for (int i = 0;i < 16; ++i)
		this->_values[i] = array[i];
}

mat4::mat4(const mat4& mat) noexcept
{
	for (int i = 0; i < 16; ++i)
		this->_values[i] = mat._values[i];
}

mat4	&mat4::operator=(const mat4& mat) noexcept
{
	for (int i = 0; i < 16; ++i)
		this->_values[i] = mat._values[i];
}

mat4	&mat4::identity() noexcept
{
	for (int i = 1; i < 15; ++i)
		this->_values[i] = 0;
	this->_values[0] = 1;
	this->_values[5] = 1;
	this->_values[10] = 1;
	this->_values[15] = 1;
	return (*this);
}

mat4	&mat4::frustum(float left, float right, float bottom, float top, float near, float far) noexcept
{
	this->_values[0] = 2 * near / (right - left);
	this->_values[1] = 0;
	this->_values[2] = 0;
	this->_values[3] = 0;
	this->_values[4] = 0;
	this->_values[5] = 2 * near / (top - bottom);
	this->_values[6] = 0;
	this->_values[7] = 0;
	this->_values[8] = (right + left) / (right - left);
	this->_values[9] = (top + bottom) / (top - bottom);
	this->_values[10] = -(far + near) / (far - near);
	this->_values[11] = -1;
	this->_values[12] = 0;
	this->_values[13] = 0;
	this->_values[14] = -2 * far * near / (far - near);
	this->_values[15] = 0;
	return (*this);
}

mat4 	&mat4::perspective(float fovy, float aspect, float near, float far) noexcept
{
	float vscale = tan(fovy * 0.5 * M_PI / 180.0) * near;
	float right = aspect * vscale;
	float left = -right;
	float top = vscale;
	float bottom = -top;
	return (this->frustum(left, right, bottom, top, near, far));
}

mat4	&mat4::translate(float x, float y, float z) noexcept
{
	static mat4	tmat;

	tmat._values[12] = x;
	tmat._values[13] = y;
	tmat._values[14] = z;
	*this *= tmat;
	return (*this);
}

mat4	&mat4::scale(const vec3& datas) noexcept
{
	static mat4	tscale;

	tscale._values[0] = datas.x();
	tscale._values[5] = datas.y();
	tscale._values[10] = datas.z();
	return ((*this) *= tscale);
}

mat4	&mat4::rotate(const vec3& axis, float theta) noexcept
{
	const float vcos = cos(theta);
	const float vsin = sin(theta);
	const float oneminuscos = 1 - vcos;

	float		values[] = {
		axis.x() * axis.x() * oneminuscos + vcos, // 0
		axis.y() * axis.x() * oneminuscos + axis.z() * vsin, // 1
		axis.z() * axis.x() * oneminuscos - axis.y() * vsin, // 2
		0, // 3
		axis.x() * axis.y() * oneminuscos - axis.z() * vsin, // 4
		axis.y() * axis.y() * oneminuscos + vcos, // 5
		axis.z() * axis.y() * oneminuscos + axis.x() * vsin, // 6
		0, // 7
		axis.x() * axis.z() * oneminuscos + axis.y() * vsin, // 8
		axis.y() * axis.z() * oneminuscos - axis.x() * vsin, // 9
		axis.z() * axis.z() * oneminuscos + vcos, // 10
		0, // 11
		0, // 12		
		0, // 13
		0, // 14
		1 // 15
	};
	mat4	trot(values);
	trot *= *this;
	*this = trot;
	return (*this);
}

mat4	&mat4::operator*=(const mat4& mat) noexcept
{
	float val1, val2, val3, val4;

	for (int i = 0; i < 4; ++i)
	{
		val1 = this->_values[i * 4];
		val2 = this->_values[i * 4 + 1];
		val3 = this->_values[i * 4 + 2];
		val4 = this->_values[i * 4 + 3];
		this->_values[i * 4] = 			val1 * mat._values[0]
									+	val2 * mat._values[1 * 4]
									+	val3 * mat._values[2 * 4]
									+	val4 * mat._values[3 * 4];
		this->_values[i * 4 + 1] = 		val1 * mat._values[1]
									+	val2 * mat._values[1 + 1 * 4]
									+	val3 * mat._values[1 + 2 * 4]
									+	val4 * mat._values[1 + 3 * 4];
		this->_values[i * 4 + 2] = 		val1 * mat._values[2]
									+	val2 * mat._values[2 + 1 * 4]
									+	val3 * mat._values[2 + 2 * 4]
									+	val4 * mat._values[2 + 3 * 4];
		this->_values[i * 4 + 3] = 		val1 * mat._values[3]
									+	val2 * mat._values[3 + 1 * 4]
									+	val3 * mat._values[3 + 2 * 4]
									+	val4 * mat._values[3 + 3 * 4];
	}
	return (*this);
}

mat4			&mat4::lookAt(const vec3& pos, const vec3& target, const vec3& up)
{
	vec3 n = target.negate().add(pos).normalize();
	vec3 u = vec3::cross(up, n).normalize();
	vec3 v = vec3::cross(n, u);

	float values[] = 
	{
		u.x(), v.x(), n.x(), 0.0f,
		u.y(), v.y(), n.y(), 0.0f,
		u.z(), v.z(), n.z(), 0.0f,
		(float)u.negate().dot(pos),
		(float)v.negate().dot(pos),
		(float)n.negate().dot(pos),
		1.0f
	};
	*this = mat4(values);
	return (*this);
}