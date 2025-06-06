#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 inVertNormal;
layout (location = 2) in vec3 inColor;
layout (location = 3) in vec2 inTexCoords;

uniform mat4 pv;
uniform mat4 model;

void main()
{
	gl_Position = pv * model * vec4(aPos, 1.0f);
}