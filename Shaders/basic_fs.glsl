#version 330 core

in vec4 color;
in vec3 oNormal;
in vec3 oPosition;

uniform vec3 ambient;
uniform vec3 diffuse;
uniform vec3 specular;
uniform mat4 projection;
uniform mat4 model;
uniform mat4 view;
uniform vec3 lightPos;
uniform vec3 ambientLight;
uniform vec3 diffuseLight;
uniform vec3 specularLight;

out vec4 outputColor;

void	main()
{
	vec3 spec = vec3(0.0);
	vec3 pixelToLight = vec3(model * vec4(lightPos, 1.0)) - vec3(model * vec4(oPosition, 1.0));
	mat3 normalMatrix = transpose(inverse(mat3(model)));
	vec3 transformedNormal = normalize(oNormal * normalMatrix);
	float brightness = dot(transformedNormal, pixelToLight) / (length(pixelToLight) * length(transformedNormal));
    brightness = clamp(brightness, 0, 1);
    if (brightness > 0.0)
    {
    	vec3 h = normalize(vec3(view * model * vec4(lightPos, 1.0)) + normalize(-vec3(view * model * vec4(oPosition, 1.0))));
    	float intSpec = max(dot(h,transformedNormal), 0.0);
        spec = specular * pow(intSpec,96);
    }
	outputColor = vec4(brightness * diffuse + spec, 1.0);
}