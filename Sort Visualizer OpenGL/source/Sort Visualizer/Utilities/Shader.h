#pragma once

#include <glad/glad.h>

#include <glm/glm.hpp>

#include <string>

class Shader {
public:
	Shader();

	void CreateShader(const std::string& vertexCode, const std::string& fragmentCode);

	void use();

	void setMat4(const std::string name, glm::mat4& value);
	void setVec3(const std::string name, glm::vec3 value);
private:
	GLuint ID;
};