#pragma once
#include <glad/glad.h>

#include <glm/glm.hpp>

#include <string>

class Shader {
public:
	Shader(const std::string& vertexCode = "NULL", const std::string& fragmentCode = "NULL");

	void use() const;

	void setMat4(const std::string name, glm::mat4& value) const;
	void setVec3(const std::string name, glm::vec3 value) const;
private:
	GLuint ID;

	void CreateShader(const std::string& vertexCode, const std::string& fragmentCode);
};