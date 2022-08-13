#include "Sort Visualizer.h"

sort::SortVisualizer::SortVisualizer(uint32_t window_width, uint32_t window_height, uint32_t min_value, uint32_t max_value, uint32_t speed, SortObject::SortType type) :
m_window(), window_width(window_width), window_height(window_height), settings{min_value, max_value, speed / 1000.0f, type}, collumns(), qRender(), sort() { }

sort::SortVisualizer::SortVisualizer(const std::string& window_width, const std::string& window_height, const std::string& min_value, const std::string& max_value, const std::string& speed, const std::string& type) :
m_window(), collumns(), qRender(), sort() {
	this->window_width = std::stoi(window_width);
	this->window_height = std::stoi(window_height);
	this->settings.min_value = std::stoi(min_value);
	this->settings.max_value = std::stoi(max_value);
	this->settings.speed = std::stoi(speed) / 1000.0f;
	std::map<const std::string, SortObject::SortType> TypeMap{
		{"BUBBLE_SORT", SortObject::BUBBLE_SORT},
		{"SELECTION_SORT", SortObject::SELECTION_SORT},
		{"INSERTION_SORT", SortObject::INSERTION_SORT},
		{"MERGE_SORT", SortObject::MERGE_SORT},
		{"HEAP_SORT", SortObject::HEAP_SORT}
	};
	this->settings.type = TypeMap[type];
}

void sort::SortVisualizer::Init() {
	this->InitOpenGL();

	glm::mat4 projection{ glm::ortho(0.0f, (float)this->window_width, 0.0f, (float)this->window_height, -1.0f, 1.0f) };
	ResourceManager::LoadShader("source/Sort Visualizer/Shaders/quadShader.vert", "source/Sort Visualizer/Shaders/quadShader.frag", "quadShader");
	ResourceManager::GetShader("quadShader").use();
	ResourceManager::GetShader("quadShader").setMat4("projection", projection);

	qRender = new quadRenderer();

	collumns = new CollumnArrayObject(settings.min_value, settings.max_value);
	collumns->SetRender(qRender);
	collumns->SetShader(ResourceManager::GetShader("quadShader"));
	sort = new SortObject(this->settings.type, settings.speed, this->collumns, this->m_window);
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

void sort::SortVisualizer::Start() const{
	sort->Start(this->window_width, this->window_height);
}

void sort::SortVisualizer::run() const {
	while (!glfwWindowShouldClose(this->m_window)) {
		Start();
	}
}