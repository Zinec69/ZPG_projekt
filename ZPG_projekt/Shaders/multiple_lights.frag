#version 330

struct Material
{
    float shininess;
};

struct Light
{
    float ambientStrength;
    float specularStrength;

    float intensity;
    float attenuation;

    int type;
    int state;

	vec3 color;
	vec3 position;
	vec3 direction;

	float cutOff;
};

#define NUM_OF_LIGHTS 100

#define POINT 1
#define SPOT 2
#define DIRECTIONAL 3

#define ON 1

in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

uniform vec3 viewPos;
uniform vec3 objectColor;

uniform Light lights[NUM_OF_LIGHTS];
uniform Material material;

uniform int numOfLights;

vec3 CalcPointLight_Phong(Light light, vec3 normal, vec3 viewDir)
{
    vec3 ambient  = light.ambientStrength * light.color;
	vec3 lightDir = normalize(light.position - FragPos);

	float diff   = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = diff * light.color;
	
	vec3 reflectDir = reflect(-lightDir, normal);
	
    float _dot    = dot(viewDir, reflectDir);
    vec3 specular = vec3(0.0);

    if (_dot >= 0.0)
    {
        float spec = pow(max(_dot, 0.0), material.shininess);
	    specular = light.specularStrength * spec * light.color;
    }

    return (ambient + diffuse + specular) * objectColor * light.intensity;
}

vec3 CalcPointLight_Blinn(Light light, vec3 normal, vec3 viewDir)
{
    vec3 ambient  = light.ambientStrength * light.color;
	vec3 lightDir = normalize(light.position - FragPos);
    
    float distance    = length(light.position - FragPos);
    float attenuation = light.attenuation / (1.0 + 0.09 * distance + 0.032 * (distance * distance));

	float diff   = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = diff * light.color * attenuation;
	
	vec3 halfwayDir = normalize(lightDir + viewDir);
	
    float _dot    = dot(normal, halfwayDir);
    vec3 specular = vec3(0.0);

    if (_dot >= 0.0)
    {
        float spec = pow(max(_dot, 0.0), material.shininess);
        specular = light.specularStrength * spec * light.color * attenuation;
    }
    
    return (ambient + diffuse + specular) * objectColor * light.intensity;
}

vec3 CalcSpotLight(Light light, vec3 normal, vec3 viewDir)
{
    vec3 ambient  = light.ambientStrength * light.color;
    vec3 lightDir = normalize(light.position - FragPos);
    
//    float theta     = dot(lightDir, normalize(-light.direction));
//    float epsilon   = 1 - light.cutOff;
//    float intensity = (theta - light.cutOff) / epsilon;
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.cutOff * 0.9;
    float intensity = clamp((theta - light.cutOff) / epsilon, 0.0, 1.0);
    
    float distance    = length(light.position - FragPos);
    float attenuation = light.attenuation / (1.0 + 0.09 * distance + 0.032 * (distance * distance));

    float diff   = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * light.color * intensity * attenuation;
    
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec      = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular   = light.specularStrength * light.color * spec * intensity * attenuation;
        
    return (diffuse + specular + ambient) * objectColor * light.intensity;
}

vec3 CalcDirectLight(Light light, vec3 normal, vec3 viewDir)
{
    vec3 ambient  = light.ambientStrength * light.color;
	vec3 lightDir = normalize(-light.direction);

	float diff   = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = diff * light.color;
	
	vec3 halfwayDir = normalize(lightDir + viewDir);
	
    float _dot    = dot(normal, halfwayDir);
    vec3 specular = vec3(0.0);

    if (_dot >= 0.0)
    {
        float spec = pow(max(_dot, 0.0), material.shininess);
        specular = light.specularStrength * spec * light.color;
    }
    
    return (ambient + diffuse + specular) * objectColor * light.intensity;
}

void main()
{
	vec3 norm    = normalize(Normal);
	vec3 viewDir = normalize(viewPos - FragPos);
	
    vec3 result = vec3(0.0);
	for (int i = 0; i < numOfLights; i++)
    {
        switch (lights[i].type)
        {
            case POINT:
                if (lights[i].state == ON)
		            result += CalcPointLight_Blinn(lights[i], norm, viewDir);
                break;
            case SPOT:
                if (lights[i].state == ON)
                    result += CalcSpotLight(lights[i], norm, viewDir);
                break;
            case DIRECTIONAL:
                if (lights[i].state == ON)
                    result += CalcDirectLight(lights[i], norm, viewDir);
                break;
        }
    }

	FragColor = vec4(result, 1.0);
}
