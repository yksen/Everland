#version 330

in vec3 fragPosition;
in vec2 fragTextureCoordinates;
in vec3 fragNormal;
in vec4 fragColor;

uniform sampler2D texture;
uniform vec4 colorDiffuse;

uniform vec3 lightColor;

out vec4 finalColor;

void main()
{
    vec4 color = vec4(0, 1, 0, 1);

    float ambientStrength = 0.5;
    vec3 ambient = ambientStrength * lightColor;

    vec3 lightDirection = normalize(vec3(1, 10, 1));
    float diffuseStrength = max(dot(fragNormal, lightDirection), 0.0);
    vec3 diffuse = diffuseStrength * lightColor;

    vec3 result = (ambient + diffuse) * color.rgb;
    finalColor = vec4(result, color.a);
}