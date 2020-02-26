#pragma once
#include "gl_core_4_5.h"
#include "glfw3.h"
class Application
{
public:

	Application(int iWindowWidth, int iWindowHeight);


private:
	
	int m_iWindowWidth;
	int m_iWindowHeight;

	GLFWwindow* m_pWindow;


};

