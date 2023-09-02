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
    float ambientStrength = 0.5;
    vec3 ambient = ambientStrength * lightColor;

    vec3 lightDir = normalize(vec3(1, 10, 1));
    float diff = max(dot(fragNormal, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 result = (ambient + diffuse) * objectColor;
    finalColor = vec4(result, 1.0);
}