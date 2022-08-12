#pragma once

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

#include "../Utilities/Shader.h"

class quadRenderer {
public:
	quadRenderer();

	void Draw(glm::vec2 position, glm::vec2 size, Shader& shader, glm::vec3 color = glm::vec3(1.0));
private:
	GLuint VAO;

	void Init();
};