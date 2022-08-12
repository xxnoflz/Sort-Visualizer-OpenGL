#include "Sort Visualizer.h"

sort::SortVisualizer::SortVisualizer(uint32_t window_width, uint32_t window_height, uint32_t min_value, uint32_t max_value, uint32_t speed, SortObject::SortType type) :
	m_window(), window_width(window_width), window_height(window_height), settings{min_value, max_value, speed / 1000.0f, type}, collumns(), qRender(), sort() { }

void sort::SortVisualizer::Init() {
	this->InitOpenGL();

	glm::mat4 projection{ glm::ortho(0.0f, (float)this->window_width, 0.0f, (float)this->window_height, -1.0f, 1.0f) };
	ResourceManager::LoadShader("source/Sort Visualizer/Shaders/quadShader.vert", "source/Sort Visualizer/Shaders/quadShader.frag", "quadShader");
	ResourceManager::GetShader("quadShader").use();
	ResourceManager::GetShader("quadShader").setMat4("projection", projection);

	qRender = new quadRenderer();

	collumns = new CollumnArrayObject(settings.min_value, settings.max_value);
	sort = new SortObject(this->settings.type, settings.speed, this->m_window, this->collumns, qRender, ResourceManager::GetShader("quadShader"));
}

void sort::SortVisualizer::InitOpenGL() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_window = glfwCreateWindow(this->window_width, this->window_height, "Sort Visualizer", nullptr, nullptr);
	glfwMakeContextCurrent(this->m_window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		glfwTerminate();

	glViewport(0, 0, this->window_width, this->window_height);
	glfwSetFramebufferSizeCallback(this->m_window, [](GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
	});
}

void sort::SortVisualizer::Render() {
	sort->Start(this->window_width, this->window_height);
}

void sort::SortVisualizer::run() {
	while (!glfwWindowShouldClose(this->m_window)) {
		Render();
	}
}