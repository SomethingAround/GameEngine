

#include "glm.hpp"
#include "ext.hpp"
#include "gl_core_4_5.h"
#include "glfw3.h"
#include "FlyCamera.h"
#include "Light.h"

#include "Mesh.h"
#include "OBJMesh.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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
	//Ends the program if the window is not created
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
	//Mesh* pMesh = new Mesh;
	OBJMesh* objMesh = new OBJMesh;

	objMesh->load("..\\Models\\meshSwordShield.obj", false);

	int x, y, n;
	unsigned char* texturePath;

	unsigned int m_uiShieldTextureID = 0;
	unsigned int m_uiShieldNormalID = 0;
	unsigned int m_uiSwordTextureID = 0;
	unsigned int m_uiSwordNormalID = 0;

	//Load Shield texture
	glGenTextures(1, &m_uiShieldTextureID);
	glBindTexture(GL_TEXTURE_2D, m_uiShieldTextureID);
	stbi_set_flip_vertically_on_load(true);

	//Gets location of the shield albedo map
	texturePath = stbi_load("../Textures/UVAlbedoMap_Shield.png", &x, &y, &n, 0);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, texturePath);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	stbi_image_free(texturePath);

	//Load Shield normal map
	glGenTextures(1, &m_uiShieldNormalID);
	glBindTexture(GL_TEXTURE_2D, m_uiShieldNormalID);
	stbi_set_flip_vertically_on_load(true);

	//Gets location of the shield normal map
	texturePath = stbi_load("../Textures/UVNormalMap_Shield.png", &x, &y, &n, 0);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, texturePath);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	stbi_image_free(texturePath);

	//Load Sword texture
	glGenTextures(1, &m_uiSwordTextureID);
	glBindTexture(GL_TEXTURE_2D, m_uiSwordTextureID);
	stbi_set_flip_vertically_on_load(true);

	//Gets location of the sword albedo map
	texturePath = stbi_load("../Textures/UVAlbedoMap_Sword.png", &x, &y, &n, 0);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, texturePath);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	stbi_image_free(texturePath);

	//Load Sword normal map
	glGenTextures(1, &m_uiSwordNormalID);
	glBindTexture(GL_TEXTURE_2D, m_uiSwordNormalID);
	stbi_set_flip_vertically_on_load(true);

	//Gets location of the sword normal map
	texturePath = stbi_load("../Textures/UVNormalMap_Sword.png", &x, &y, &n, 0);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, texturePath);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	stbi_image_free(texturePath);

	unsigned int uiVertexShaderID = 0;
	unsigned int uiFragementShaderID = 0;
	unsigned int uiShaderProgramID = 0;

	std::string sShaderData;

	//Gets the location of the vertex shader
	std::ifstream inFileStream("..\\Shaders\\PhongLightVert.glsl", std::ifstream::in);

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

	//Checks if the vertex shader has loaded successfully
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



	//Gets the location of the fragment shader
	std::ifstream frag_in_file_stream("..\\Shaders\\PhongLightFrag2.glsl", std::ifstream::in);

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

	//Checks if the fragment shader has loaded successfully
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



	//Creates the shader
	uiShaderProgramID = glCreateProgram();
	glAttachShader(uiShaderProgramID, uiVertexShaderID);
	glAttachShader(uiShaderProgramID, uiFragementShaderID);

	glLinkProgram(uiShaderProgramID);


	success = GL_FALSE;
	glGetProgramiv(uiShaderProgramID, GL_LINK_STATUS, &success);

	//Checks if the shader has loaded successfully
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
	}

	float fCurrentFrame = glfwGetTime();
	float fDeltaTime = 0.0f;
	float fLastFrame = 0.0f;

	//Set cursor to the middle of the screen and hide it
	glfwSetCursorPos(pWindow, iWindowWidth * 0.5, iWindowHeight * 0.5);
	ShowCursor(false);

	//Creates light
	const int nLightCount = 2;
	Light light[nLightCount];

	//Sets lights specualr and diffuse
	light[0].m_v3Specular = {1, 1, 1};
	light[0].m_v3Diffuse = {0.0f, 0.75f, 0.75f};

	light[1].m_v3Specular = { 1, 1, 1 };
	light[1].m_v3Diffuse = { 0.75f, 0.0f, 0.0f };

	glm::vec3 v3AmbientLight = {0.1f,0.1f,0.1f};

	//Game Loop
	while (glfwWindowShouldClose(pWindow) == false && glfwGetKey(pWindow, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Calculate deltatime
		fCurrentFrame = glfwGetTime();
		fDeltaTime = fCurrentFrame - fLastFrame;
		fLastFrame = fCurrentFrame;

		pCamera->Update(fDeltaTime);

		//Sets light direction 
		light[0].m_v3Direction = glm::normalize(glm::vec3(-1, 0, 0));
		light[1].m_v3Direction = glm::normalize(glm::vec3(0, -1, 0));

		glm::vec4 color = glm::vec4(0.5f);

		glUseProgram(uiShaderProgramID);

		auto uniform_location = glGetUniformLocation(uiShaderProgramID, "light[0].Ia");
		glUniform3fv(uniform_location, 1, glm::value_ptr(v3AmbientLight));

		uniform_location = glGetUniformLocation(uiShaderProgramID, "light[0].Id");
		glUniform3fv(uniform_location, 1, glm::value_ptr(light[0].m_v3Diffuse));

		uniform_location = glGetUniformLocation(uiShaderProgramID, "light[0].Is");
		glUniform3fv(uniform_location, 1, glm::value_ptr(light[0].m_v3Specular));

		uniform_location = glGetUniformLocation(uiShaderProgramID, "light[1].Ia");
		glUniform3fv(uniform_location, 1, glm::value_ptr(v3AmbientLight));

		uniform_location = glGetUniformLocation(uiShaderProgramID, "light[1].Id");
		glUniform3fv(uniform_location, 1, glm::value_ptr(light[1].m_v3Diffuse));

		uniform_location = glGetUniformLocation(uiShaderProgramID, "light[1].Is");
		glUniform3fv(uniform_location, 1, glm::value_ptr(light[1].m_v3Specular));

		uniform_location = glGetUniformLocation(uiShaderProgramID, "Ka");
		glUniform3fv(uniform_location, 1, glm::value_ptr(glm::vec3(1)));

		uniform_location = glGetUniformLocation(uiShaderProgramID, "Kd");
		glUniform3fv(uniform_location, 1, glm::value_ptr(glm::vec3(1)));

		uniform_location = glGetUniformLocation(uiShaderProgramID, "Ks");
		glUniform3fv(uniform_location, 1, glm::value_ptr(glm::vec3(1)));

		uniform_location = glGetUniformLocation(uiShaderProgramID, "v3CameraPosition");
		glUniform3fv(uniform_location, 1, glm::value_ptr(glm::vec3(glm::inverse(pCamera->GetView())[3])));

		uniform_location = glGetUniformLocation(uiShaderProgramID, "light[0].v3LightDirection");
		glUniform3fv(uniform_location, 1, glm::value_ptr(light[0].m_v3Direction));

		uniform_location = glGetUniformLocation(uiShaderProgramID, "light[1].v3LightDirection");
		glUniform3fv(uniform_location, 1, glm::value_ptr(light[1].m_v3Direction));

		uniform_location = glGetUniformLocation(uiShaderProgramID, "m4ProjectionView");
		glUniformMatrix4fv(uniform_location, 1, false, glm::value_ptr(pCamera->GetProjectionView()));

		uniform_location = glGetUniformLocation(uiShaderProgramID, "m4Model");
		glUniformMatrix4fv(uniform_location, 1, false, glm::value_ptr(m4Model));

		uniform_location = glGetUniformLocation(uiShaderProgramID, "lightCount");
		glUniform1i(uniform_location, nLightCount);

		uniform_location = glGetUniformLocation(uiShaderProgramID, "m3Normal");
		glUniformMatrix3fv(uniform_location, 1, false, glm::value_ptr(glm::inverseTranspose(glm::mat3(m4Model))));

		uniform_location = glGetUniformLocation(uiShaderProgramID, "fSpecularPower");
		glUniform1f(uniform_location, 32);

		//Passes texture to shield mesh
		uniform_location = glGetUniformLocation(uiShaderProgramID, "diffuseTexture");
		glUniform1i(uniform_location, 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_uiShieldTextureID);

		uniform_location = glGetUniformLocation(uiShaderProgramID, "normalTexture");
		glUniform1i(uniform_location, 1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, m_uiShieldNormalID);

		//Draws shield with texture
		glBindVertexArray(objMesh->m_meshChunks[0].vao);
		glDrawElements(GL_TRIANGLES, objMesh->m_meshChunks[0].indexCount, GL_UNSIGNED_INT, 0);


		//Passes texture to sword mesh
		uniform_location = glGetUniformLocation(uiShaderProgramID, "diffuseTexture");
		glUniform1i(uniform_location, 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_uiSwordTextureID);

		uniform_location = glGetUniformLocation(uiShaderProgramID, "normalTexture");
		glUniform1i(uniform_location, 1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, m_uiSwordNormalID);

		//Draws sword texture
		glBindVertexArray(objMesh->m_meshChunks[1].vao);
		glDrawElements(GL_TRIANGLES, objMesh->m_meshChunks[1].indexCount, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(pWindow);
		glfwPollEvents();
	}

	glfwDestroyWindow(pWindow);
	glfwTerminate();

	//Delete pointers
	delete pCamera;
	pCamera = nullptr;

	delete objMesh;
	objMesh = nullptr;

	return 0;
}