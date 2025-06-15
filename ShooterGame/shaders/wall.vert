#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec2 TexCoord;
out vec3 vertNormal;
out vec3 fragPos;

uniform mat4 pv;
uniform mat4 model;
uniform vec2 uvScale;

void main()
{
    TexCoord = aTexCoord * uvScale;

    vec4 worldPos = model * vec4(aPos, 1.0);
    fragPos = worldPos.xyz;

    mat3 normalMatrix = transpose(inverse(mat3(model)));
    vertNormal = normalize(normalMatrix * aNormal);

    gl_Position = pv * worldPos;
}
