#pragma once

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

class Shader
{
public:
	Shader(const char* vPath, const char* fPath);

	void use();
	unsigned int getID();

	void setInt(const char* uniform, int value);
	void setFloat(const char* uniform, float value);
	void setVec3(const char* uniform, glm::vec3 value);
	void setMat4(const char* uniform, glm::mat4 value);

private:
	unsigned int shaderProgram;
};