#include "mesh.h"

using Gema::Mesh;

std::map<std::string, Mesh *>	Mesh::_register_meshs;

void	Mesh::draw() noexcept
{
	if (!this->_is_build)
	{
		float	vertices[this->_vertices.size() * 3];
		int i = 0;
		for (auto it : this->_vertices)
		{
			vertices[i * 3] = it.x();
			vertices[i * 3 + 1] = it.y();
			vertices[i * 3 + 2] = it.z();
			++i;
		}
		glGenBuffers(2, this->_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, this->_vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, this->_vertices.size() * 3 * sizeof(float), vertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_vbo[1]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->_indices.size() * sizeof(float), this->_indices.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	glBindBuffer(GL_ARRAY_BUFFER, this->_vbo[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_vbo[1]);
	glDrawElements(GL_TRIANGLES, this->_indices.size(), GL_UNSIGNED_INT, (void *)0);
	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}