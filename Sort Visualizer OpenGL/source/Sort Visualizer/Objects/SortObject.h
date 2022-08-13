#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "CollumnArrayObject.h"

#include <vector>

class SortObject {
	struct TimeHandler {
		float currentTime;
		float lastTime;
		float deltaTime;
	};
public:
	enum SortType {
		BUBBLE_SORT,
		SELECTION_SORT,
		INSERTION_SORT,
		MERGE_SORT,
		HEAP_SORT,
		COMPLETED
	};

	SortObject(SortType type, float speed, CollumnArrayObject* object, GLFWwindow* main_window);

	void UpdateTime();
	void StartRender() const;
	void RenderSort(const int32_t window_width, const uint32_t window_height, const int iter, const int next_iter);
	void RenderCompletedSort(const int32_t window_width, const uint32_t window_height) const;
	void EndRender() const;

	void Start(uint32_t window_width, uint32_t window_height);
private:
	SortType type;
	float speed;
	CollumnArrayObject* object;
	GLFWwindow* window;
	TimeHandler time;

	void BubbleSort(const uint32_t window_width, const uint32_t window_height);
	void InsertionSort(const uint32_t window_width, const uint32_t window_height);
	void SelectionSort(const uint32_t window_width, const uint32_t window_height);
	void MergeSort(const int left, const int right, const uint32_t window_width, const uint32_t window_height);
	void Merge(const int left, const int mid, const int right, const uint32_t window_width, const uint32_t winodow_height);
	void HeapSort(const uint32_t window_width, const uint32_t window_height);
	void Heapify(const int size, const int node);
};