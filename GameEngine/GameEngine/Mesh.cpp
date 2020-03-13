#include "Mesh.h"
#include "gl_core_4_5.h"



Mesh::Mesh()
{
	m_uiTriCount = 0;

	m_uiVAO = 0;
	m_uiVBO = 0;
	m_uiIBO = 0;

	glGenVertexArrays(1, &m_uiVAO);
	glGenBuffers(1, &m_uiVBO);
	glGenBuffers(1, &m_uiIBO);

	InitialiseQuad();
}

Mesh::~Mesh()
{
	glDeleteBuffers(1, &m_uiVAO);
	glDeleteBuffers(1, &m_uiVBO);
	glDeleteBuffers(1, &m_uiIBO);

	delete data;
	data = nullptr;
	//glDeleteTextures(1, &m_uiTexture);
}

//Creates a quad
void Mesh::InitialiseQuad()
{
	Vertex vertices[4] =
	{
		Vertex{{-0.25f,	 0.25f, 0.25, 1.0f}, {0.0f, 1.0f, 0.0f, 0.0f}, {0, 0}},
		Vertex{{-0.25f,	0.25f, -0.25, 1.0f}, {0.0f, 1.0f, 0.0f, 0.0f}, {0, 1}},
		Vertex{{ 0.25f,	 0.25f, 0.25, 1.0f}, {0.0f, 1.0f, 0.0f, 0.0f}, {1, 0}},
		Vertex{{ 0.25f,	0.25f, -0.25, 1.0f}, {0.0f, 1.0f, 0.0f, 0.0f}, {1, 1}}
	};

	//Order to draw from which points
	 m_auiIndex =
	{
		//Front
		0,1,2,
		2,1,3
	};
	

	//Binds the VAO
	glBindVertexArray(m_uiVAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_uiVBO);
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Vertex), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_uiIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_auiIndex.size() * sizeof(int), m_auiIndex.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_TRUE, sizeof(Vertex), (void*)16);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

//Draws the mesh
void Mesh::Draw()
{
	glBindVertexArray(m_uiVAO);
	glDrawElements(GL_TRIANGLES, m_auiIndex.size(), GL_UNSIGNED_INT, 0);
}
