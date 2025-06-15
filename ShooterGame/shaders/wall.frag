#version 460 core

struct Light {
    int type; 
    vec3 position;
    vec3 direction;
    float cutOff;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float constant;
    float linear;
    float quadratic;
};

in vec2 TexCoord;
in vec3 fragPos;
in vec3 vertNormal;

out vec4 FragColor;

uniform sampler2D diffuseTex;
uniform sampler2D normalTex;
uniform sampler2D roughnessTex;

uniform vec3 viewPos;

#define MAX_LIGHTS 4
uniform int lights_count;
uniform Light light[MAX_LIGHTS];

uniform float shininess = 64;

float getAtten(int i)
{
    float dist = distance(light[i].position, fragPos);
    float attenuation = 1.0 / (light[i].constant + light[i].linear * dist + light[i].quadratic * dist * dist);
    return attenuation;
}

vec3 CalcDiffuseOnly(int i, vec3 lightDir, vec3 norm, vec3 diffuseColor)
{
    float diff_koef = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light[i].diffuse * diff_koef * diffuseColor;

    return diffuse;
}

void main()
{
    vec3 diffuseColor = texture(diffuseTex, TexCoord).rgb;

    vec3 normalMap = texture(normalTex, TexCoord).rgb;
    normalMap = normalMap * 2.0 - 1.0;
    vec3 norm = normalize(vertNormal);

    float roughness = texture(roughnessTex, TexCoord).r;

    vec3 result = vec3(0.0);

    for (int i = 0; i < lights_count; i++)
    {
        vec3 lresult = vec3(0.0);
        if (light[i].type == 1) // Directional light
        {
            vec3 lightDir = normalize(-light[i].direction);
            vec3 ambient = light[i].ambient * diffuseColor;
            vec3 diffspec = CalcDiffuseOnly(i, lightDir, norm, diffuseColor);
            lresult = ambient + diffspec;
        }
        else
        {
            vec3 lightDir = normalize(light[i].position - fragPos);
            float attenuation = getAtten(i);
            vec3 ambient = light[i].ambient * diffuseColor;
            vec3 diffspec = CalcDiffuseOnly(i, lightDir, norm, diffuseColor);

            if (light[i].type == 2) // Point light
            {
                lresult = (ambient + diffspec) * attenuation;
            }
            else if (light[i].type == 3) // Spot light
            {
                float angle = dot(lightDir, normalize(-light[i].direction));
                if (angle > light[i].cutOff)
                {
                    // smoothstep: edge0 < edge1
                    float intensity = smoothstep(light[i].cutOff * 0.95, light[i].cutOff, angle);
                    lresult = (ambient + diffspec * intensity) * attenuation;
                }
                else
                {
                    lresult = ambient * attenuation;
                }
            }
        }
        result += lresult;
    }

    FragColor = vec4(result, 1.0);
}

