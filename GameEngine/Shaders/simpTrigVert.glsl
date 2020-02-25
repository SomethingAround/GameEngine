#version 450

layout (location = 0) in vec3 local_position;
layout (location = 1) in vec4 normal;

uniform mat4 projection_view_matrix;
uniform mat4 model_matrix;
uniform float time;

out vec3 pos;

void main()
{
	pos = local_position;
	
	pos.y += 1/(tan(1/cos(1/sin(time))) * pos.x);
	//pos.x += (((3 * (1/cos(time))) * (0.5 * (1/sin(time * time * time))) * (2 * (1/tan(time)))) / tan(time)) * pos.y;
	//pos.x += 1/(tan(1/cos(1/sin(time))) * pos.y);
	//pos.y += 1/sin(1/(cos(time)) * pos.x);
	//pos.x += sqrt(pow(2,sin(pow(1/cos(log(tan(time))),sqrt(time))))) * pos.y;
	//pos.x += sqrt(pow(2,(((1/tan(2 * time))*time)/(1/sin(2*time))))) * pos.y;
	//pos.y += sqrt(pow(2,(((1/tan(2 * time))*time)/(1/sin(2*time))))) * pos.y;
	//pos.z += sqrt(pow(2,(((1/tan(2 * time))*time)/(1/sin(2*time))))) * pos.y;
	//pos.x += sqrt(pow(2,(((1/cos(2 * time))*time)/(1/sin(2*time))))) * pos.y;
	gl_Position = (projection_view_matrix * model_matrix) * vec4(pos, 1);
}

//1/tan(1/sin(1/cos(time))) + 0.66
//1/tan(1/cos(1/sin(time)));
//((3 * (1/cos(time))) * (0.5(1/sin(time * time * time))) * (2(1/tan(time)))) / tan(time)
//sin(pow(1/cos(log(tan(time))),sqrt(time))) * pos.y
//sqrt(pow(2,(((1/tan(2 * time))*time)/(1/sin(time)))))