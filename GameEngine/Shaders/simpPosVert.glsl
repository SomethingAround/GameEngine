#version 450

layout (location = 0) in vec3 local_position;
layout (location = 1) in vec4 normal;

uniform mat4 projection_view_matrix;
uniform mat4 model_matrix;

out vec3 pos;

void main()
{
	gl_Position = (projection_view_matrix * model_matrix) * vec4(local_position, 1);
	
	pos = local_position;
}