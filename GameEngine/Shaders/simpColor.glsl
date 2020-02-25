#version 450

uniform vec4 v4Colour = vec4(1,1,1,1);

in vec3 v3OutNormal;

out vec4 v4FinalColour;

void main()
{
	v4FinalColour = vec4(v3OutNormal,1) * 0.1;
}