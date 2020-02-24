#include "Mesh.h"
#include "gl_core_4_5.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Mesh::Mesh()
{
	m_uiTriCount = 0;

	m_uiVAO = 0;
	m_uiVBO = 0;
	m_uiIBO = 0;

	//data 
	data = stbi_load("..\\Images\\direction_test.jpg", &x, &y, &n, 0);

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
	glDeleteTextures(1, &m_uiTexture);
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

	Vertex vertices[4] =
	{
		Vertex{{-0.25f,	 0.25f, 0.25},	{0, 0}},
		Vertex{{-0.25f,	-0.25f, 0.25},	{0, 1}},
		Vertex{{ 0.25f,	 0.25f, 0.25},	{1, 0}},
		Vertex{{ 0.25f,	-0.25f, 0.25},	{1, 1}}
	};
	////Front Verts
	//vertices[0].v3Position = glm::vec3(-0.25f, 0.25f, 0.25);
	//vertices[0].v2UV = glm::vec2(0, 0);

	//vertices[1].v3Position = glm::vec3(-0.25f, -0.25f, 0.25);
	//vertices[1].v2UV = glm::vec2(0, 1);

	//vertices[2].v3Position = glm::vec3(0.25f, 0.25f, 0.25);
	//vertices[2].v2UV = glm::vec2(1, 0);

	//vertices[3].v3Position = glm::vec3(0.25f, -0.25f, 0.25);
	//vertices[3].v2UV = glm::vec2(1, 1);


	////Back Verts
	//vertices[4].v3Position = glm::vec3(-0.25f, 0.25f, -0.25);
	//vertices[5].v3Position = glm::vec3(-0.25f, -0.25f, -0.25);
	//vertices[6].v3Position = glm::vec3(0.25f, 0.25f, -0.25);
	//vertices[7].v3Position = glm::vec3(0.25f, -0.25f, -0.25);



	 m_auiIndex =
	{
		//Front
		0,1,2,
		2,1,3
		////Back
		//4,6,5,
		//6,7,5,
		////Left
		//4,5,0,
		//0,5,1,
		////Right
		//2,3,6,
		//6,3,7,
		////Bottom
		//1,5,3,
		//3,5,7,
		////Top
		//4,0,6,
		//6,0,2
	};
	 

	 glBindVertexArray(m_uiVAO);

	 glBindBuffer(GL_ARRAY_BUFFER, m_uiVBO);
	 glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Vertex), vertices, GL_STATIC_DRAW);

	 glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_uiIBO);
	 glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_auiIndex.size() * sizeof(int), m_auiIndex.data(), GL_STATIC_DRAW);

	 glEnableVertexAttribArray(0);
	 glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	 glEnableVertexAttribArray(1);
	 glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(glm::vec3)));

	 glBindVertexArray(0);
	 glBindBuffer(GL_ARRAY_BUFFER, 0);
	 glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	 glGenTextures(1, &m_uiTexture);
	 glBindTexture(GL_TEXTURE_2D, m_uiTexture);
	 glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, data);



	 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	 glBindTexture(GL_TEXTURE_2D, 0);

	 stbi_image_free(data);
}

void Mesh::Draw()
{
	glBindTexture(GL_TEXTURE_2D, m_uiTexture);
	glBindVertexArray(m_uiVAO);
	//glDrawArrays(GL_TRIANGLES, 0, number_of_verts);
	glDrawElements(GL_TRIANGLES, m_auiIndex.size(), GL_UNSIGNED_INT, 0);


}
