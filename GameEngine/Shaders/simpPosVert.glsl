#version 450

layout (location = 0) in vec4 v4LocalPosition;
layout (location = 1) in vec4 v4Normal;

uniform mat4 m4ProjectionView;
uniform mat4 m4Model;

out vec4 v4Position;

void main()
{
	gl_Position = (m4ProjectionView * m4Model) * v4LocalPosition;
	
	v4Position = v4LocalPosition;
}