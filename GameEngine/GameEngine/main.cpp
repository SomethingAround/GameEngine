#include "glm.hpp"
#include "ext.hpp"
#include "gl_core_4_5.h"
#include "glfw3.h"
#include "FlyCamera.h"
#include "Mesh.h"

#include <iostream>
#include <fstream>
#include <sstream>

int main()
{
	//Check for Memory Leaks
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//Initialize OpenGL
	if (glfwInit() == false)
	{
		return -1;
	}

	int iWindowWidth = 1280;
	int iWindowHeight = 720;

	GLFWwindow* pWindow = glfwCreateWindow(1280, 720, "Computer Graphics", nullptr, nullptr);

	if (pWindow == nullptr)
	{
		glfwTerminate();

		return -2;
	}

	glfwMakeContextCurrent(pWindow);

	if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
	{
		glfwDestroyWindow(pWindow);
		glfwTerminate();

		return -3;
	}

	auto major = ogl_GetMajorVersion();
	auto minor = ogl_GetMinorVersion();
	printf("GL: %i.%i\n", major, minor);

	//Camera
	FlyCamera* pCamera = new FlyCamera(glm::vec3(0, 0, 1), glm::vec3(0), 1.507f, 16.0f / 9.0f, 0.1f, 50.0f);
	glm::mat4 m4Model = glm::mat4(1.0f);
	Mesh* pMesh = new Mesh;

	unsigned int uiVertexShaderID = 0;
	unsigned int uiFragementShaderID = 0;
	unsigned int uiShaderProgramID = 0;

	std::string sShaderData;
	std::ifstream inFileStream("..\\Shaders\\simpVert.glsl", std::ifstream::in);

	std::stringstream stringStream;
	//Load the source into a string for compilation
	if (inFileStream.is_open())
	{
		stringStream << inFileStream.rdbuf();
		sShaderData = stringStream.str();
		inFileStream.close();
	}
	//Allocate space for shader program
	uiVertexShaderID = glCreateShader(GL_VERTEX_SHADER);

	//conver to raw char*
	const char* data = sShaderData.c_str();

	//send in the char* to shader location
	glShaderSource(uiVertexShaderID, 1, (const GLchar**)&data, 0);

	//Build
	glCompileShader(uiVertexShaderID);

	//Check the shader compiled
	GLint success = GL_FALSE;
	glGetShaderiv(uiVertexShaderID, GL_COMPILE_STATUS, &success);

	if (success == GL_FALSE)
	{
		//Get the length of IoenGL error message
		GLint log_length = 0;
		glGetShaderiv(uiShaderProgramID, GL_INFO_LOG_LENGTH, &log_length);

		//Create the error message
		char* log = new char[log_length];

		//Copy the error from the buffer
		glGetShaderInfoLog(uiShaderProgramID, log_length, 0, log);

		//Create the error message
		std::string error_message(log);
		error_message += "SHADER_FAILED_TO_COMPILE";
		printf(error_message.c_str());

		//Clean up anyway
		delete[] log;
	}




	std::ifstream frag_in_file_stream("..\\Shaders\\simpColor.glsl", std::ifstream::in);

	std::stringstream fragment_string_stream;
	//Load the source into a string for compilation
	if (frag_in_file_stream.is_open())
	{
		fragment_string_stream << frag_in_file_stream.rdbuf();
		sShaderData = fragment_string_stream.str();
		frag_in_file_stream.close();
	}
	//Allocate space for shader program
	uiFragementShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	//conver to raw char*
	data = sShaderData.c_str();

	//send in the char* to shader location
	glShaderSource(uiFragementShaderID, 1, (const GLchar**)&data, 0);

	//Build
	glCompileShader(uiFragementShaderID);

	//Check the shader compiled
	success = GL_FALSE;
	glGetShaderiv(uiFragementShaderID, GL_COMPILE_STATUS, &success);

	if (success == GL_FALSE)
	{
		//Get the length of IoenGL error message
		GLint log_length = 0;
		glGetShaderiv(uiShaderProgramID, GL_INFO_LOG_LENGTH, &log_length);

		//Create the error message
		char* log = new char[log_length];

		//Copy the error from the buffer
		glGetShaderInfoLog(uiShaderProgramID, log_length, 0, log);

		//Create the error message
		std::string error_message(log);
		error_message += "SHADER_FAILED_TO_COMPILE";
		printf(error_message.c_str());

		//Clean up anyway
		delete[] log;
	}




	uiShaderProgramID = glCreateProgram();
	glAttachShader(uiShaderProgramID, uiVertexShaderID);
	glAttachShader(uiShaderProgramID, uiFragementShaderID);

	glLinkProgram(uiShaderProgramID);


	success = GL_FALSE;
	glGetProgramiv(uiShaderProgramID, GL_LINK_STATUS, &success);
	if (success == GL_FALSE)
	{
		//Get the length of IoenGL error message
		GLint log_length = 0;
		glGetProgramiv(uiShaderProgramID, GL_INFO_LOG_LENGTH, &log_length);

		//Create the error message
		char* log = new char[log_length];

		//Copy the error from the buffer
		glGetProgramInfoLog(uiShaderProgramID, log_length, 0, log);

		//Create the error message
		std::string error_message(log);
		error_message += "SHADER_FAILED_TO_COMPILE";
		printf(error_message.c_str());

		//Clean up anyway
		delete[] log;
		//printf("Shader Linking Failed");
	}

	float fLineWidth = 1.0f;
	bool bHit = false;

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(fLineWidth);

	float fCurrentFrame = glfwGetTime();
	float fDeltaTime = 0.0f;
	float fLastFrame = 0.0f;

	glfwSetCursorPos(pWindow, iWindowWidth * 0.5, iWindowHeight * 0.5);
	ShowCursor(true);
	//Game Loop
	while (glfwWindowShouldClose(pWindow) == false && glfwGetKey(pWindow, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		//glClearColor(0.25f, 0.25f, 0.25f, 1);
		//glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glLineWidth(fLineWidth);

		fCurrentFrame = glfwGetTime();
		fDeltaTime = fCurrentFrame - fLastFrame;
		fLastFrame = fCurrentFrame;

		pCamera->Update(fDeltaTime);

		//model = glm::rotate(model, 0.016f, glm::vec3(0.5f));

		//glm::mat4 pv = projection * view;

		glm::vec4 color = glm::vec4(0.5f);
	
		glUseProgram(uiShaderProgramID);

		auto uniform_location = glGetUniformLocation(uiShaderProgramID, "projection_view_matrix");
		glUniformMatrix4fv(uniform_location, 1, false, glm::value_ptr(pCamera->GetProjectionView()));

		uniform_location = glGetUniformLocation(uiShaderProgramID, "model_matrix");
		glUniformMatrix4fv(uniform_location, 1, false, glm::value_ptr(m4Model));

		uniform_location = glGetUniformLocation(uiShaderProgramID, "color");
		glUniform4fv(uniform_location, 1, glm::value_ptr(color));

		pMesh->Draw();
		//glBindVertexArray(VAO);
		////glDrawArrays(GL_TRIANGLES, 0, number_of_verts);
		//glDrawElements(GL_TRIANGLES, index_buffer_size, GL_UNSIGNED_INT, 0);


		if (fLineWidth >= 10.0f && !bHit)
		{
			bHit = true;
		}
		else if(fLineWidth <= 0.0f && bHit)
		{
			bHit = false;
		}

		if (bHit == true)
		{
			fLineWidth -= 0.75f;
		}
		else
		{
			fLineWidth += 0.75f;
		}

		glfwSwapBuffers(pWindow);
		glfwPollEvents();
	}

	glfwDestroyWindow(pWindow);
	glfwTerminate();

	delete pCamera;
	delete pMesh;

	return 0;
}