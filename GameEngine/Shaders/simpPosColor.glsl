#version 450

uniform vec4 v4Colour = vec4(1,1,1,1);
uniform float fFragTime; 

in vec4 v4Position;

out vec4 v4FinalColour;

void main()
{
	v4FinalColour = v4Position;
}