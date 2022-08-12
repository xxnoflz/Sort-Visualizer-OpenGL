#include "CollumnArrayObject.h"

CollumnArrayObject::CollumnArrayObject(uint32_t min_value, uint32_t max_value) {
	this->CreateNumbersArray(min_value, max_value);

	m_max = *std::max_element(this->numbers.begin(), this->numbers.end());
}

void CollumnArrayObject::CreateNumbersArray(uint32_t min_value, uint32_t max_value) {
	std::random_device rd;
	std::mt19937 gen(rd());
	for (uint32_t iter{ min_value }; iter <= max_value; ++iter)
		this->numbers.push_back(iter);
	std::shuffle(this->numbers.begin(), this->numbers.end(), gen);
}

void CollumnArrayObject::DrawCollumns(quadRenderer* qRender, Shader& shader, uint32_t window_width, uint32_t window_height, uint32_t current_object, uint32_t next_object) {
	float collumn_width{ (float(window_width) / this->numbers.size()) - collumn_padding};
	for (uint32_t iter{}; iter < this->numbers.size(); ++iter) {
		uint32_t collumn_height{ (this->numbers[iter] * window_height) / this->m_max};
		if(iter == current_object)
			qRender->Draw(glm::vec2(0.0f + (collumn_width * iter) + (collumn_padding * iter), 0.0f), glm::vec2(collumn_width, collumn_height), shader, glm::vec3(0.0, 1.0, 0.0));
		else if (iter == next_object)
			qRender->Draw(glm::vec2(0.0f + (collumn_width * iter) + (collumn_padding * iter), 0.0f), glm::vec2(collumn_width, collumn_height), shader, glm::vec3(1.0, 0.0, 0.0));
		else
			qRender->Draw(glm::vec2(0.0f + (collumn_width * iter) + (collumn_padding * iter), 0.0f), glm::vec2(collumn_width, collumn_height), shader);
	}
}

void CollumnArrayObject::DrawCompleteCollumns(quadRenderer* qRender, Shader& shader, uint32_t window_width, uint32_t window_height) {
	float collumn_width{ (float(window_width) / this->numbers.size()) - collumn_padding };
	for (uint32_t iter{}; iter < this->numbers.size(); ++iter) {
		uint32_t collumn_height{ (this->numbers[iter] * window_height) / this->m_max };
		qRender->Draw(glm::vec2(0.0f + (collumn_width * iter) + (collumn_padding * iter), 0.0f), glm::vec2(collumn_width, collumn_height), shader, glm::vec3(1.0, 1.0, 0.0));
	}
}

std::vector<int>& CollumnArrayObject::GetVector() {
	return this->numbers;
}