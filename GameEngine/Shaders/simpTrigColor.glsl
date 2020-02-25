#version 450

uniform vec4 color = vec4(1,1,1,1);
uniform float fragTime; 

in vec3 pos;

out vec4 final_color;

void main()
{

	final_color = vec4(sqrt(pow(2,sin(pow(1/cos(log(tan(fragTime))),sqrt(fragTime))))), (((3 * (1/cos(fragTime))) * (0.5 * (1/sin(fragTime * fragTime * fragTime))) * (2 * (1/tan(fragTime)))) / tan(fragTime)), 1/(tan(1/cos(1/sin(fragTime)))),1);
}