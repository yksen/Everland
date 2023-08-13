#version 330

in vec3 fragPosition;
in vec2 fragTextureCoordinates;
in vec3 fragNormal;
in vec4 fragColor;

uniform sampler2D texture;
uniform vec4 colorDiffuse;

uniform vec3 lightColor;
uniform vec3 objectColor;

out vec4 finalColor;

void main()
{
    // ambient
    float ambientStrength = 0.5;
    vec3 ambient = ambientStrength * lightColor;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(vec3(FragPos.x + 1, 192, FragPos.z + 1));
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
            
    vec3 result = (ambient + diffuse) * objectColor;
    FragColor = vec4(result, 1.0);
} 