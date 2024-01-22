#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 fs_Color;

void main()
{
	fs_Color = aColor;
	gl_Position = vec4(aPos, 1);
}