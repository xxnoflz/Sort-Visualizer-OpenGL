#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "CollumnArrayObject.h"

#include <vector>

class SortObject {
public:
	enum SortType {
		BUBBLE_SORT,
		SELECTION_SORT,
		INSERTION_SORT,
		MERGE_SORT,
		HEAP_SORT,
		COMPLETED
	};
	struct TimeHandler {
		float currentTime;
		float lastTime;
		float deltaTime;
	};

	SortObject(SortType type, float speed, GLFWwindow* window, CollumnArrayObject* object, quadRenderer* qRender, Shader& shader);

	void UpdateTime();
	void StartRender();
	void Render(int32_t window_width, uint32_t window_height, int iter, int next_iter);
	void EndRender();

	void Start(uint32_t window_width, uint32_t window_height);
private:
	SortType type;
	float speed;

	GLFWwindow* window;
	CollumnArrayObject* object;
	quadRenderer* qRender; 
	Shader shader;

	TimeHandler time;

	void BubbleSort(uint32_t window_width, uint32_t window_height);
	void InsertionSort(uint32_t window_width, uint32_t window_height);
	void SelectionSort(uint32_t window_width, uint32_t window_height);
	void MergeSort(int left, int right, uint32_t window_width, uint32_t window_height);
	void Merge(int left, int mid, int right, uint32_t window_width, uint32_t winodow_height);
	void HeapSort(uint32_t window_width, uint32_t window_height);
	void Heapify(int size, int node);
};