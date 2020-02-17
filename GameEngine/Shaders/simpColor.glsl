#version 450

uniform vec4 color = vec4(1,1,1,1);

in vec3 outNormal;

out vec4 final_color;

void main()
{
	final_color = vec4(outNormal,1) * 0.1;
}