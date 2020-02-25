#version 450 // Phong Lighting Frag Shader

in vec3 v3Normal;

uniform vec3 v3LightDirection;

out vec4 v4FragColour;

void main()
{
	vec3 N = normalize(v3Normal);
	vec3 L = normalize(v3LightDirection);
	
	float fLambertTerm = max(0, min(1, dot(N,-L)));
	
	v4FragColour = vec4(fLambertTerm, fLambertTerm, fLambertTerm,1);
}