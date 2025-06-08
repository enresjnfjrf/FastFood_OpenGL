#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

uniform mat4 pv;
uniform mat4 model;
uniform vec2 uvScale;

void main()
{
	TexCoord = aTexCoord * uvScale;

	vec4 vertPos = model * vec4(aPos, 1.0f);
	gl_Position = pv * vertPos;
	
}