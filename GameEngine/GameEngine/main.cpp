#include "glm.hpp"
#include "ext.hpp"
#include "gl_core_4_5.h"
#include "glfw3.h"

#include <iostream>
#include <fstream>
#include <sstream>

int main()
{
	//Initialize OpenGL
	if (glfwInit() == false)
	{
		return -1;
	}

	GLFWwindow* window = glfwCreateWindow(1280, 720, "Computer Graphics", nullptr, nullptr);

	if (window == nullptr)
	{
		glfwTerminate();

		return -2;
	}

	glfwMakeContextCurrent(window);

	if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
	{
		glfwDestroyWindow(window);
		glfwTerminate();

		return -3;
	}

	auto major = ogl_GetMajorVersion();
	auto minor = ogl_GetMinorVersion();
	printf("GL: %i.%i\n", major, minor);

	//glm::vec3 verticies[] =
	//{
	//	glm::vec3(-0.5f, 0.5f,0),
	//	glm::vec3(0.5f, 0.5f,0),
	//	glm::vec3(-0.5f, -0.5f,0),
	//	glm::vec3(0.5f, 0.5f,0),
	//	glm::vec3(-0.5f, -0.5f,0),
	//	glm::vec3(0.5f,-0.5f,0)
	//};
	//int number_of_verts = 6;

	//glm::vec3 verticies[] =
	//{
	//	glm::vec3(-0.5f, 0.5f,0),
	//	glm::vec3(-0.5f,-0.5f,0),
	//	glm::vec3(0.5f, 0.5f,0),
	//	glm::vec3(0.5f,-0.5f,0)
	//};

	glm::vec3 verticies[] =
	{
		//Front Verts
		glm::vec3(-0.25f, 0.25f, 0.25),
		glm::vec3(-0.25f,-0.25f, 0.25),
		glm::vec3 (0.25f, 0.25f, 0.25),
		glm::vec3 (0.25f,-0.25f, 0.25),
		//Back Verts
		glm::vec3(-0.25f, 0.25f,-0.25),
		glm::vec3(-0.25f,-0.25f,-0.25),
		glm::vec3( 0.25f, 0.25f,-0.25),
		glm::vec3( 0.25f,-0.25f,-0.25)
	};

	const int index_buffer_size = 36;

	int index_buffer[index_buffer_size]
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
		6,0,2};

	//Create and load mesh
	unsigned int VAO;
	unsigned int VBO;
	unsigned int IBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &IBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(glm::vec3), verticies, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_size * sizeof(int), index_buffer, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//Camera
	glm::mat4 projection = glm::perspective(1.507f, 16.0f / 9.0f, 0.1f, 50.0f);
	glm::mat4 view = glm::lookAt(glm::vec3(0, 0, 1), glm::vec3(0), glm::vec3(0, 1, 0));
	glm::mat4 model = glm::mat4(1.0f);

	unsigned int vertex_shader_ID = 0;
	unsigned int fragment_shader_ID = 0;
	unsigned shader_program_ID = 0;

	std::string shader_data;
	std::ifstream in_file_stream("..\\Shaders\\simpVert.glsl", std::ifstream::in);

	std::stringstream string_stream;
	//Load the source into a string for compilation
	if (in_file_stream.is_open())
	{
		string_stream << in_file_stream.rdbuf();
		shader_data = string_stream.str();
		in_file_stream.close();
	}
	//Allocate space for shader program
	vertex_shader_ID = glCreateShader(GL_VERTEX_SHADER);

	//conver to raw char*
	const char* data = shader_data.c_str();

	//send in the char* to shader location
	glShaderSource(vertex_shader_ID, 1, (const GLchar**)&data, 0);

	//Build
	glCompileShader(vertex_shader_ID);

	//Check the shader compiled
	GLint success = GL_FALSE;
	glGetShaderiv(vertex_shader_ID, GL_COMPILE_STATUS, &success);

	if (success == GL_FALSE)
	{
		//Get the length of IoenGL error message
		GLint log_length = 0;
		glGetShaderiv(shader_program_ID, GL_INFO_LOG_LENGTH, &log_length);

		//Create the error message
		char* log = new char[log_length];

		//Copy the error from the buffer
		glGetShaderInfoLog(shader_program_ID, log_length, 0, log);

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
		shader_data = fragment_string_stream.str();
		frag_in_file_stream.close();
	}
	//Allocate space for shader program
	fragment_shader_ID = glCreateShader(GL_FRAGMENT_SHADER);

	//conver to raw char*
	data = shader_data.c_str();

	//send in the char* to shader location
	glShaderSource(fragment_shader_ID, 1, (const GLchar**)&data, 0);

	//Build
	glCompileShader(fragment_shader_ID);

	//Check the shader compiled
	success = GL_FALSE;
	glGetShaderiv(fragment_shader_ID, GL_COMPILE_STATUS, &success);

	if (success == GL_FALSE)
	{
		//Get the length of IoenGL error message
		GLint log_length = 0;
		glGetShaderiv(shader_program_ID, GL_INFO_LOG_LENGTH, &log_length);

		//Create the error message
		char* log = new char[log_length];

		//Copy the error from the buffer
		glGetShaderInfoLog(shader_program_ID, log_length, 0, log);

		//Create the error message
		std::string error_message(log);
		error_message += "SHADER_FAILED_TO_COMPILE";
		printf(error_message.c_str());

		//Clean up anyway
		delete[] log;
	}




	shader_program_ID = glCreateProgram();
	glAttachShader(shader_program_ID, vertex_shader_ID);
	glAttachShader(shader_program_ID, fragment_shader_ID);

	glLinkProgram(shader_program_ID);


	success = GL_FALSE;
	glGetProgramiv(shader_program_ID, GL_LINK_STATUS, &success);
	if (success == GL_FALSE)
	{
		//Get the length of IoenGL error message
		GLint log_length = 0;
		glGetProgramiv(shader_program_ID, GL_INFO_LOG_LENGTH, &log_length);

		//Create the error message
		char* log = new char[log_length];

		//Copy the error from the buffer
		glGetProgramInfoLog(shader_program_ID, log_length, 0, log);

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

	glPolygonMode(GL_BACK, GL_LINE);
	glLineWidth(fLineWidth);

	//Game Loop
	while (glfwWindowShouldClose(window) == false && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		//glClearColor(0.25f, 0.25f, 0.25f, 1);
		//glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glLineWidth(fLineWidth);

		model = glm::rotate(model, 0.016f, glm::vec3(0.5f));

		glm::mat4 pv = projection * view;

		glm::vec4 color = glm::vec4(0.5f);

		glUseProgram(shader_program_ID);

		auto uniform_location = glGetUniformLocation(shader_program_ID, "projection_view_matrix");
		glUniformMatrix4fv(uniform_location, 1, false, glm::value_ptr(pv));

		uniform_location = glGetUniformLocation(shader_program_ID, "model_matrix");
		glUniformMatrix4fv(uniform_location, 1, false, glm::value_ptr(model));

		uniform_location = glGetUniformLocation(shader_program_ID, "color");
		glUniform4fv(uniform_location, 1, glm::value_ptr(color));

		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, number_of_verts);
		glDrawElements(GL_TRIANGLES, index_buffer_size, GL_UNSIGNED_INT, 0);



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

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteBuffers(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}