#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 inVertNormal;
layout (location = 2) in vec2 inTexCoords;
layout (location = 3) in vec3 inTangent;
layout (location = 4) in vec3 inBiTangent;

out vec2 texCoords;
out vec3 vertNormal;
out vec3 fragPos;
out mat3 TBN;

uniform mat4 pv;
uniform mat4 model;

void main()
{
	vec4 vertPos = model * vec4(aPos, 1.0f);
	gl_Position = pv * vertPos;
	vertNormal = mat3(model) * inVertNormal;
	texCoords = inTexCoords;
	fragPos = vertPos.xyz;
}