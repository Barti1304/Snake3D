#version 330 core

in vec2 fs_TexCoord;

out vec4 FragColor;

uniform sampler2D activeTexture;

void main()
{
	FragColor = texture(activeTexture, fs_TexCoord);
}