#version 450 // Phong Lighting Frag Shader

in vec2 v2Tex;
in vec3 v3Normal;
in vec3 v3Tangent;
in vec3 v3BiTangent;
in vec4 v4Position;

uniform vec3 v3CameraPosition;

uniform sampler2D diffuseTexture;
uniform sampler2D specularTexture;
uniform sampler2D normalTexture;

struct Light
{
	vec3 Ia;
	vec3 Id;
	vec3 Is;
	vec3 v3LightDirection;
};

uniform Light light[8];

uniform int lightCount;

uniform vec3 Ka;
uniform vec3 Kd;
uniform vec3 Ks;
uniform float fSpecularPower;

out vec4 v4FragColour;

void main()
{
	vec3 N = normalize(v3Normal);
	vec3 T = normalize(v3Tangent);
	vec3 B = normalize(v3BiTangent);
	
	mat3 TBN = mat3(T,B,N);
	
	vec3 texDiffuse = texture(diffuseTexture, v2Tex).rgb;
	vec3 texSpecular = texture(specularTexture, v2Tex).rgb;
	vec3 texNormal = texture(normalTexture, v2Tex).rgb;
	
	N = TBN * (texNormal * 2 - 1);
	
	vec3 V = normalize(v3CameraPosition - v4Position.xyz);
	
	for(int i = 0; i < lightCount; ++i)
	{
		vec3 L = normalize(light[i].v3LightDirection);
		
		float fLambertTerm = max(0, dot(N,-L));
		
		vec3 R = reflect(L, N);
		
		float specularTerm = pow(max(0, dot(R, V)), fSpecularPower);
		
		vec3 ambient = light[i].Ia * Ka;
		vec3 diffuse = light[i].Id * Kd * texDiffuse * fLambertTerm;
		vec3 specular = light[i].Is * Ks * texSpecular * specularTerm;
		
		v4FragColour += vec4(ambient + diffuse + specular, 1);
	}
}