#version 460 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 FragPos;

// texture samplers
uniform sampler2D texture1;

void main()
{
	// FragColor = texture(texture1, TexCoord);
	FragColor = vec4(FragPos, 1.0);
}