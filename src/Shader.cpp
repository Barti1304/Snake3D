#include "Shader.h"

Shader::Shader(const char* vPath, const char* fPath)
{
	std::fstream vRead(vPath);
	std::fstream fRead(fPath);

	std::stringstream vStream;
	std::stringstream fStream;
	vStream << vRead.rdbuf();
	fStream << fRead.rdbuf();

	std::string vString = vStream.str();
	std::string fString = fStream.str();

	const char* vSource = vString.c_str();
	const char* fSource = fString.c_str();

	unsigned int vShader = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vShader, 1, &vSource, 0);
	glShaderSource(fShader, 1, &fSource, 0);

	glCompileShader(vShader);
	glCompileShader(fShader);

	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vShader);
	glAttachShader(shaderProgram, fShader);

	glLinkProgram(shaderProgram);

	glDeleteShader(vShader);
	glDeleteShader(fShader);

	std::cout << vSource << "\n-----\n" << fSource << '\n';
}

void Shader::use()
{
	glUseProgram(shaderProgram);
}

unsigned int Shader::getID()
{
	return shaderProgram;
}

void Shader::setInt(const char* uniform, int value)
{
	glUniform1i(glGetUniformLocation(shaderProgram, uniform), value);
}

void Shader::setFloat(const char* uniform, float value)
{
	glUniform1f(glGetUniformLocation(shaderProgram, uniform), value);
}

void Shader::setVec3(const char* uniform, glm::vec3 value)
{
	glUniform3f(glGetUniformLocation(shaderProgram, uniform), value.x, value.y, value.z);
}

void Shader::setMat4(const char* uniform, glm::mat4 value)
{
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, uniform), 1, GL_FALSE, glm::value_ptr(value));
}