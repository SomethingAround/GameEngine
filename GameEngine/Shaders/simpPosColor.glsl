#version 450

uniform vec4 color = vec4(1,1,1,1);
uniform float fragTime; 

in vec3 pos;

out vec4 final_color;

void main()
{
	final_color = vec4(pos,1);
}