#version 460 core

out vec4 light_color;

uniform vec3 lightColor;

void  main()
{
	light_color =vec4(lightColor, 1.0f);
}