#pragma once
#include "glm.hpp"
#include "gl_core_4_5.h"

#include <vector>
#include <assert.h>

class Mesh
{
public:
	Mesh();
	virtual ~Mesh();

	struct Vertex
	{
		glm::vec3 v3Position;
	};

	std::vector<glm::vec3> m_av3Vericies;
	std::vector<unsigned int> m_auiIndex;

	void InitialiseQuad();

	virtual void Draw();

private:

	unsigned int m_uiTriCount;
	unsigned int m_uiVAO, m_uiVBO, m_uiIBO;
};