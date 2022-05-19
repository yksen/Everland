#version 460 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 FragPos;

// texture samplers
uniform sampler2D texture1;
uniform vec3 blockColor;

void main()
{
	// FragColor = texture(texture1, TexCoord);
	FragColor = vec4(blockColor, 1.0);
}