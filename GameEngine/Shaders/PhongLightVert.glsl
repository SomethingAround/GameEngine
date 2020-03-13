#version 450 // Phong Lighting Vert shader

layout(location = 0) in vec4 v4LocalPosition;
layout(location = 1) in vec4 v4Normal;
layout(location = 2) in vec2 v2TexCoord;
layout(location = 3) in vec4 v4Tangent;

out vec2 v2Tex;
out vec3 v3Normal;
out vec3 v3Tangent;
out vec3 v3BiTangent;
out vec4 v4Position;

uniform mat4 m4ProjectionView;

uniform mat4 m4Model;

uniform mat3 m3Normal;

void main()
{
	v2Tex = v2TexCoord;
	v4Position = m4Model * v4LocalPosition;
	v3Normal = m3Normal * v4Normal.xyz;
	v3Tangent = m3Normal * v4Tangent.xyz;
	v3BiTangent = cross(v3Normal, v3Tangent) * v4Tangent.w;
    gl_Position = (m4ProjectionView * m4Model) * v4LocalPosition;
}