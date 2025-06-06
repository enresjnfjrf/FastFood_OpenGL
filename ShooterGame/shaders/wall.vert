#version 460 core
layout (location = 0) in vec3 aPos;

uniform mat4 pv;
uniform mat4 model;

void main()
{
	vec4 vertPos = model * vec4(aPos, 1.0f);
	gl_Position = pv * vertPos;
	
}