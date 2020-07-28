#pragma once
#include "glm.hpp"

#include <vector>
#include <assert.h>

class Mesh
{
public:
	Mesh();
	virtual ~Mesh();

	struct Vertex
	{
		glm::vec4 v4Position;
		glm::vec4 v4Normal;
		glm::vec2 v2UV;
	};

	std::vector<unsigned int> m_auiIndex;

	//Creates a quad
	void InitialiseQuad();

	virtual void Draw();

private:

	unsigned int m_uiTriCount;
	unsigned int m_uiVAO, m_uiVBO, m_uiIBO;

	unsigned int m_uiTexture;
	
	int x, y, n;
	
	unsigned char* data;
	unsigned int athing;
	unsigned int athing2;
	unsigned int athing3;
};