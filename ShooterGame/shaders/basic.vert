#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 inVertNormal;
layout (location = 2) in vec3 inColor;
layout (location = 3) in vec2 inTexCoords;

out vec3 outColor;
out vec2 texCoords;
out vec3 vertNormal;
out vec3 fragPos;

uniform mat4 pv;
uniform mat4 model;

void main()
{
	vec4 vertPos = model * vec4(aPos, 1.0f);
	gl_Position = pv * vertPos;
	vertNormal = mat3(model) * inVertNormal;
	outColor = inColor;
	texCoords = inTexCoords;
	fragPos = vertPos.xyz;
}
