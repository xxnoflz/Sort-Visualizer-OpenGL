#include "quadRenderer.h"

quadRenderer::quadRenderer() : VAO() {
	this->Init();
}

void quadRenderer::Init() {
	std::vector<float> vertices{
		0.0, 0.0,
		1.0, 0.0,
		0.0, 1.0,

		1.0, 0.0,
		0.0, 1.0,
		1.0, 1.0
	};
	GLuint VBO;

	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &this->VAO);
	glBindVertexArray(this->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void quadRenderer::Draw(glm::vec2 position, glm::vec2 size, Shader& shader, glm::vec3 color) {
	shader.use();
	glm::mat4 model{ glm::mat4(1.0) };
	model = glm::translate(model, glm::vec3(position, 0.0));
	model = glm::scale(model, glm::vec3(size, 1.0));
	shader.setMat4("model", model);
	shader.setVec3("color", color);

	glBindVertexArray(this->VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}