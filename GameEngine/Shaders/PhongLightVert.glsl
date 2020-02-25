#version 450 // Phong Lighting Vert shader

layout(location = 0) in vec4 v4LocalPosition;
layout(location = 1) in vec4 v4Normal;

out vec3 v3Normal;

uniform mat4 m4ProjectionView;
uniform mat4 m4Model;

uniform mat3 m3Normal;

void main()
{
	v3Normal = m3Normal * v4Normal.xyz;
    gl_Position = (m4ProjectionView * m4Model) * v4LocalPosition;
}