#version 460 core

in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D diffuseTex;
uniform sampler2D normalTex;  
uniform sampler2D roughnessTex;

void main() {
    vec3 diffuseColor = texture(diffuseTex, TexCoord).rgb;
    vec3 normalColor = texture(normalTex, TexCoord).rgb;
    float roughnessValue = texture(roughnessTex, TexCoord).r;

    FragColor = vec4(diffuseColor * normalColor, roughnessValue);
}