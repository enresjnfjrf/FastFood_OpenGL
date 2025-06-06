#version 460 core

struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

struct Light{
	int type;
	float cutOff;
	vec3 position;
	vec3 direction;
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

out vec4 frag_color;

uniform sampler2D ourTexture;
uniform vec3 viewPos;
uniform Material material;
uniform Light light;

float getAtten()
{
	float dist = distance(light.position, fragPos); 
	float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * dist * dist);
	return attenuation;
}

vec3 getDiffuse(vec3 lightDir, vec3 norm)
{
	float diff_koef = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse =  light.diffuse * (diff_koef * material.diffuse);

	return diffuse;
}

vec3 getSpecular(vec3 lightDir, vec3 norm)
{
	vec3 reflectDir = reflect(lightDir, norm);
	vec3 viewDir = normalize(fragPos - viewPos);
	float spec_koef = pow(max(dot(viewDir, reflectDir) , 0.0f), material.shininess);
	vec3 specular = light.specular * (spec_koef * material.specular);

	return specular;
}

void  main()
{
	vec3 norm = normalize(vertNormal);
	if(light.type == 1)  //Direction light
	{
		vec3 lightDir = -light.direction;

		vec3 ambient = light.ambient * material.ambient;

		vec3 diffuse = getDiffuse(lightDir, norm);

		vec3 specular = getSpecular(lightDir, norm);

		frag_color = texture(ourTexture,texCoords) * vec4(ambient + diffuse + specular, 1.0f);
	}
	else
	{
		vec3 lightDir = -normalize(fragPos - light.position);
		if(light.type == 0)   //Point light
		{
			float attenuation = getAtten();
	
			vec3 ambient = light.ambient * material.ambient * attenuation;

			vec3 diffuse = getDiffuse(lightDir, norm);
			diffuse *= attenuation;

			vec3 specular = getSpecular(lightDir, norm);
			specular *= attenuation;

			frag_color = texture(ourTexture,texCoords) * vec4(ambient + diffuse + specular, 1.0f);
		}
		else if (light.type == 2) 
		{
			float angle = acos(dot(lightDir, normalize(-light.direction)));

			if(angle <= 2.0f * light.cutOff)
			{
				float koef = 1.0f;
				if(angle >= light.cutOff)
				{
					koef = (2.0 * light.cutOff - angle) / light.cutOff;
				}

				float attenuation = getAtten();
	
				vec3 ambient = light.ambient * material.ambient * attenuation;

				vec3 diffuse = getDiffuse(lightDir, norm);
				diffuse *= attenuation * koef;

				vec3 specular = getSpecular(lightDir, norm);
				specular *= attenuation * koef;

				frag_color = texture(ourTexture,texCoords) * vec4(ambient + diffuse + specular, 1.0f);
			}
			else
			{
				frag_color = texture(ourTexture,texCoords) * vec4(material.ambient * light.ambient, 1.0f);
			}
		}
	}
}