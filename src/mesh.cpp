#include "mesh.h"
#include "renderer.h"
#include "light.h"
#include <iostream>

using Gema::Mesh;
using Gema::Material;
using Gema::Shader;
using Gema::Renderer;
using Gema::Light;

std::map<std::string, Mesh *>	Mesh::_register_meshs;

bool	Mesh::draw() noexcept
{
	if (!this->_is_build)
	{
		if (!this->_shader)
		{
			this->_shader = new Shader("Shaders/basic_vs.glsl", "Shaders/basic_fs.glsl");
			this->_shader->load();
		}
		if (!this->_shader || !this->_shader->isLoad())
			return (false);
		float	vertices[this->_vertices.size() * 3];
		int i = 0;
		for (auto it : this->_vertices)
		{
			vertices[i * 3] = it.x();
			vertices[i * 3 + 1] = it.y();
			vertices[i * 3 + 2] = it.z();
			// std::cout << "mesh : (" << it.x() << ", " << it.y() << ", " << it.z() << ")" << std::endl; 
			++i;
		}
		float 	normals[this->_normals.size() * 3];
		i = 0;
		for (auto it : this->_normals)
		{
			normals[i * 3] = it.x();
			normals[i * 3 + 1] = it.y();
			normals[i * 3 + 2] = it.z();
			// std::cout << "mesh normale : (" << it.x() << ", " << it.y() << ", " << it.z() << ")" << std::endl; 
			++i;
		}
		// for (auto it2 : this->_indices)
		// {
		// 	std::cout << "indice (" << it2 << ")" << std::endl;
		// }
		glGenBuffers(3, this->_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, this->_vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, this->_vertices.size() * 3 * sizeof(float), vertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, this->_vbo[2]);
		glBufferData(GL_ARRAY_BUFFER, this->_normals.size() * 3 * sizeof(float), normals, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_vbo[1]);
		// glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->_indices.size() * sizeof(uint32_t), this->_indices.data(), GL_STATIC_DRAW);
		// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		this->_is_build = true;
	}
	if (!this->_material && !this->_material_name.empty())
	{
		this->_material = Material::get(this->_material_name);
		if (!this->_material)
			return (false);
	}
	glUseProgram(this->_shader->id());
	glUniformMatrix4fv(this->_shader->uniformLocation("projection"), 1, GL_FALSE, Renderer::singleton()->projMatrix().values());
	glUniformMatrix4fv(this->_shader->uniformLocation("view"), 1, GL_FALSE, Renderer::singleton()->viewMatrix().values());
	glUniformMatrix4fv(this->_shader->uniformLocation("model"), 1, GL_FALSE, Renderer::singleton()->worldMatrix().values());
	static Light	*l = nullptr;
	if (!l)
	{
		l = new Light();
		l->setPosition(vec3(3, 3, 3));
	}
	if (l)
	{
		glUniform3fv(this->_shader->uniformLocation("lightPos"), 1, l->pos().values());
		glUniform3fv(this->_shader->uniformLocation("ambientLight"), 1, l->ambient().values());
		glUniform3fv(this->_shader->uniformLocation("diffuseLight"), 1, l->diffuse().values());
		glUniform3fv(this->_shader->uniformLocation("specularLight"), 1, l->specular().values());
	}
	if (this->_material)
	{
		glUniform3fv(this->_shader->uniformLocation("ambient"), 1, this->_material->ambient().values());
		glUniform3fv(this->_shader->uniformLocation("diffuse"), 1, this->_material->diffuse().values());
		glUniform3fv(this->_shader->uniformLocation("specular"), 1, this->_material->specular().values());
	}
	else
	{
		float vals[3] = {1.0, 1.0, 1.0};
		glUniform3fv(this->_shader->uniformLocation("ambient"), 1, vals);
		glUniform3fv(this->_shader->uniformLocation("diffuse"), 1, vals);
		glUniform3fv(this->_shader->uniformLocation("specular"), 1, vals);
	}
	glBindBuffer(GL_ARRAY_BUFFER, this->_vbo[2]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, this->_vbo[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_TRIANGLES, 0, this->_vertices.size() * 3);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glUseProgram(0);
	return (true);
}