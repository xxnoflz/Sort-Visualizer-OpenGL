#pragma once
#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

#include "../Utilities/Shader.h"

class quadRenderer {
public:
	quadRenderer();

	void Draw(const glm::vec2 position, const glm::vec2 size, const Shader& shader, const glm::vec3 color = glm::vec3(1.0)) const;
private:
	GLuint VAO;

	void Init();
};