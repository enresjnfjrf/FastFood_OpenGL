﻿#version 460 core

struct Light{
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

in vec3 outColor;
in vec2 texCoords;
in vec3 fragPos;
in vec3 vertNormal;
in mat3 TBN;

out vec4 frag_color;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform sampler2D texture_normal1;
uniform float shininess = 64.0f;


uniform vec3 viewPos;
#define MAX_LIGHTS 4
uniform int lights_count;
uniform Light light[MAX_LIGHTS];

float getAtten(int i)
{
    float dist = distance(light[i].position, fragPos);
    float attenuation = 1.0 / (light[i].constant + light[i].linear*dist + light[i].quadratic * dist * dist);
    return attenuation;
}

vec3 CalcDiffusePlusSpecular(int i, vec3 lightDir)
{
    //vec3 norm = texture(texture_normal1, texCoords).rgb;
    //norm = normalize(norm * 2.0f - 1.0f);

    vec3 norm = normalize(vertNormal);
    float diff_koef = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light[i].diffuse * diff_koef * vec3(texture(texture_diffuse1, texCoords));

    // specular
    vec3 reflectDir = reflect(lightDir, norm);
    vec3 viewDir = normalize(fragPos-viewPos);
    float spec_koef = pow(max(dot(viewDir, reflectDir), 0.0f), shininess);
    vec3 specular = light[i].specular * spec_koef * vec3(texture(texture_specular1, texCoords));

    return diffuse + specular;
}

void main()
{
    vec3 result = vec3(0.0); // ← инициализируем результирующий цвет

    for (int i = 0; i < lights_count; i++)
    {
        vec3 lresult = vec3(0.0);

        if (light[i].type == 1) // Directional Light
        {
            vec3 lightDir = -light[i].direction;
            vec3 ambient = light[i].ambient * texture(texture_diffuse1, texCoords).rgb;
            vec3 diffspec = CalcDiffusePlusSpecular(i, lightDir);
            lresult = ambient + diffspec;
        }
        else 
        { 
            vec3 lightDir = normalize(light[i].position - fragPos);

            if (light[i].type == 2) // Point Light
            {
                float attenuation = getAtten(i);
                vec3 ambient = light[i].ambient * vec3(texture(texture_diffuse1, texCoords));
                vec3 diffspec = CalcDiffusePlusSpecular(i, lightDir);
                lresult = (ambient + diffspec) * attenuation;
            }
            else if (light[i].type == 3) // SpotLight
            {
                float angle = acos(dot(lightDir, normalize(-light[i].direction)));

                if (angle <= light[i].cutOff * 2.0f)
                {
                    float koef = 1.0f;
                    if (angle >= light[i].cutOff)
                    {
                        koef = (light[i].cutOff * 2.0f - angle) / light[i].cutOff;
                    }

                    float attenuation = getAtten(i);
                    vec3 ambient = light[i].ambient * vec3(texture(texture_diffuse1, texCoords));
                    vec3 diffspec = CalcDiffusePlusSpecular(i, lightDir) * koef;

                    lresult = (ambient + diffspec) * attenuation;
                }
                else
                {
                    lresult = vec3(texture(texture_diffuse1, texCoords)) * light[i].ambient;
                }
            }
        }

        result += lresult;
    }

    frag_color = vec4(result, 1.0);
}
