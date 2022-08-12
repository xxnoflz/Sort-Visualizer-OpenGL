#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Utilities/ResourceManager.h"
#include "Render/quadRenderer.h"
#include "Objects/CollumnArrayObject.h"
#include "Objects/SortObject.h"

namespace sort {
	class SortVisualizer {
	public:
		struct SortSettings {
			uint32_t min_value;
			uint32_t max_value;
			float speed;
			SortObject::SortType type;
		};

		SortVisualizer(uint32_t window_width, uint32_t window_height, uint32_t min_value, uint32_t max_value, uint32_t speed, SortObject::SortType type);

		void Init();
		void InitOpenGL();

		void Render();

		void run();
	private:
		GLFWwindow* m_window;
		uint32_t window_width;
		uint32_t window_height;

		SortSettings settings;

		quadRenderer* qRender;

		CollumnArrayObject* collumns;
		SortObject* sort;
	};
}