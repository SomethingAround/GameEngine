#include "Mesh.h"

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
}

void Mesh::InitialiseQuad()
{
	//vertices =
	//{
	//	//Front Verts
	//	glm::vec3(-0.25f, 0.25f, 0.25),
	//	glm::vec3(-0.25f,-0.25f, 0.25),
	//	glm::vec3(0.25f, 0.25f, 0.25),
	//	glm::vec3(0.25f,-0.25f, 0.25),
	//	//Back Verts
	//	glm::vec3(-0.25f, 0.25f,-0.25),
	//	glm::vec3(-0.25f,-0.25f,-0.25),
	//	glm::vec3(0.25f, 0.25f,-0.25),
	//	glm::vec3(0.25f,-0.25f,-0.25)
	//};
	Vertex vertices[8];
	//Front Verts
	vertices[0].v3Position = glm::vec3(-0.25f, 0.25f, 0.25);
	vertices[1].v3Position = glm::vec3(-0.25f, -0.25f, 0.25);
	vertices[2].v3Position = glm::vec3(0.25f, 0.25f, 0.25);
	vertices[3].v3Position = glm::vec3(0.25f, -0.25f, 0.25);
	//Back Verts
	vertices[4].v3Position = glm::vec3(-0.25f, 0.25f, -0.25);
	vertices[5].v3Position = glm::vec3(-0.25f, -0.25f, -0.25);
	vertices[6].v3Position = glm::vec3(0.25f, 0.25f, -0.25);
	vertices[7].v3Position = glm::vec3(0.25f, -0.25f, -0.25);



	 m_auiIndex =
	{
		//Front
		0,1,2,
		2,1,3,
		//Back
		4,6,5,
		6,7,5,
		//Left
		4,5,0,
		0,5,1,
		//Right
		2,3,6,
		6,3,7,
		//Bottom
		1,5,3,
		3,5,7,
		//Top
		4,0,6,
		6,0,2
	};

	 glBindVertexArray(m_uiVAO);

	 glBindBuffer(GL_ARRAY_BUFFER, m_uiVBO);
	 glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(Vertex), vertices, GL_STATIC_DRAW);

	 glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_uiIBO);
	 glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_auiIndex.size() * sizeof(int), m_auiIndex.data(), GL_STATIC_DRAW);

	 glEnableVertexAttribArray(0);
	 glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);

	 glBindVertexArray(0);
	 glBindBuffer(GL_ARRAY_BUFFER, 0);
	 glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::Draw()
{
	glBindVertexArray(m_uiVAO);
	//glDrawArrays(GL_TRIANGLES, 0, number_of_verts);
	glDrawElements(GL_TRIANGLES, m_auiIndex.size(), GL_UNSIGNED_INT, 0);
}
