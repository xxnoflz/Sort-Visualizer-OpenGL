#include "SortObject.h"

SortObject::SortObject(SortType type, float speed, CollumnArrayObject* object, GLFWwindow* main_window) :
	type(type), time(), speed(speed), window(main_window), object(object) {}

void SortObject::Start(uint32_t window_width, uint32_t window_height) {
	switch (type) {
		case BUBBLE_SORT:
			this->BubbleSort(window_width, window_height);
			break;
		case SELECTION_SORT:
			this->SelectionSort(window_width, window_height);
			break;
		case INSERTION_SORT:
			this->InsertionSort(window_width, window_height);
			break;
		case MERGE_SORT:
			this->MergeSort(0, (int)this->object->GetVector().size() - 1, window_width, window_height);
			type = COMPLETED;
			break;
		case HEAP_SORT:
			this->HeapSort(window_width, window_height);
			type = COMPLETED;
			break;
		case COMPLETED:
			this->RenderCompletedSort(window_width, window_height);
			break;
	}
}

void SortObject::UpdateTime() {
	time.currentTime = float(glfwGetTime());
	time.deltaTime = time.currentTime - time.lastTime;
	time.lastTime = time.currentTime;
}

void SortObject::StartRender() const {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);
}

void SortObject::RenderSort(const int32_t window_width, const uint32_t window_height, const int iter, const int next_iter) {
	float accumulator{};
	while (accumulator <= speed) {
		StartRender();
		UpdateTime();

		object->DrawCollumns(window_width, window_height, iter, next_iter);
		accumulator += time.deltaTime;

		EndRender();
	}
}

void SortObject::RenderCompletedSort(const int32_t window_width, const uint32_t window_height) const {
	StartRender();
	object->DrawCompleteCollumns(window_width, window_height);
	EndRender();
}

void SortObject::EndRender() const {
	glfwSwapBuffers(this->window);
	glfwPollEvents();
}


//Sorting algorithms
void SortObject::BubbleSort(const uint32_t window_width, const uint32_t window_height) {
	uint64_t limit{ object->GetVector().size() - 1 };
	while (type != COMPLETED) {
		int swapped_iter{};
		for (int iter{}; iter < limit; ++iter) {
			if (object->GetVector()[iter] > object->GetVector()[iter + 1]) {
				RenderSort(window_width, window_height, iter, iter + 1);
				std::swap(object->GetVector()[iter], object->GetVector()[iter + 1]);
				swapped_iter = iter;
			}
			RenderSort(window_width, window_height, iter, iter + 1);
		}
		if (!swapped_iter) 
			type = COMPLETED;
		limit = swapped_iter;
	}
}

void SortObject::SelectionSort(const uint32_t window_width, const uint32_t window_height) {
	for (int first_iter{}; first_iter < object->GetVector().size() - 1; ++first_iter) {
		int min_item{ first_iter };
		for (int second_iter{ first_iter + 1 }; second_iter < object->GetVector().size(); ++second_iter)
			if (object->GetVector()[second_iter] < object->GetVector()[min_item])
				min_item = second_iter;
		RenderSort(window_width, window_height, first_iter, min_item);
		if (first_iter != min_item)
			std::swap(object->GetVector()[min_item], object->GetVector()[first_iter]);
		RenderSort(window_width, window_height, first_iter, min_item);
	}
	type = COMPLETED;
}

void SortObject::InsertionSort(const uint32_t window_width, const uint32_t window_height) {
	for (int iter{}; iter < object->GetVector().size(); ++iter) {
		for (int in_iter{ iter }; in_iter > 0; --in_iter) {
			bool swapped{ false };
			if (object->GetVector()[in_iter] < object->GetVector()[in_iter - 1]) { 
				RenderSort(window_width, window_height, iter, in_iter);
				std::swap(object->GetVector()[in_iter], object->GetVector()[in_iter - 1]); 
				swapped = true;
			}
			RenderSort(window_width, window_height, iter, in_iter);
			if (!swapped)
				break;
		}
	}
	type = COMPLETED;
}

void SortObject::MergeSort(const int left, const int right, const uint32_t window_width, const uint32_t window_height) {
	RenderSort(window_width, window_height, left, right);
	if (left >= right)
		return;
	int mid{ (left + right) / 2 };
	this->MergeSort(left, mid, window_width, window_width);
	this->MergeSort(mid + 1, right, window_width, window_height);
	this->Merge(left, mid, right, window_width, window_height);
	RenderSort(window_width, window_height, left, right);
}

void SortObject::Merge(const int left, const int mid, const int right, const uint32_t window_width, const uint32_t winodow_height) {
	const int leftSubArray{ mid - left + 1 };
	const int rightSubArray{ right - mid };

	std::vector<int> leftArray(leftSubArray);
	std::vector<int> rightArray(rightSubArray);
	for (int it{}; it < leftSubArray; ++it)
		leftArray[it] = this->object->GetVector()[left + it];
	for (int it{}; it < rightSubArray; ++it)
		rightArray[it] = this->object->GetVector()[mid + 1 + it];

	int indexOfLeftArray{};
	int indexOfRightArray{};
	int indexOfMergedArray{ left };

	while (indexOfLeftArray < leftSubArray && indexOfRightArray < rightSubArray) {
		if (leftArray[indexOfLeftArray] <= rightArray[indexOfRightArray]) {
			this->object->GetVector()[indexOfMergedArray] = leftArray[indexOfLeftArray];
			++indexOfLeftArray;
		}
		else {
			this->object->GetVector()[indexOfMergedArray] = rightArray[indexOfRightArray];
			++indexOfRightArray;
		}
		++indexOfMergedArray;
	}
	while (indexOfLeftArray < leftSubArray) {
		this->object->GetVector()[indexOfMergedArray] = leftArray[indexOfLeftArray];
		++indexOfLeftArray;
		++indexOfMergedArray;
	}
	while (indexOfRightArray < rightSubArray) {
		this->object->GetVector()[indexOfMergedArray] = rightArray[indexOfRightArray];
		++indexOfRightArray;
		++indexOfMergedArray;
	}
}

void SortObject::HeapSort(const uint32_t window_width, const uint32_t window_height) {
	RenderSort(window_width, window_height, 0, 0);
	for (int it{ (int)object->GetVector().size() / 2 - 1 }; it >= 0; --it)
		Heapify((int)object->GetVector().size(), it);
	for (int it{ (int)object->GetVector().size() - 1 }; it > 0; --it) {
		RenderSort(window_width, window_height, 0, it);
		std::swap(object->GetVector()[0], object->GetVector()[it]);
		Heapify(it, 0);
		RenderSort(window_width, window_height, 0, it);
	}
}

void SortObject::Heapify(const int size, const int node) {
	int largest{ node };

	int left{ 2 * node + 1 };
	int right{ 2 * node + 2 };
	if (left < size && this->object->GetVector()[left] > this->object->GetVector()[largest])
		largest = left;
	if (right < size && this->object->GetVector()[right] > this->object->GetVector()[largest])
		largest = right;
	if (largest != node) {
		std::swap(this->object->GetVector()[largest], this->object->GetVector()[node]);
		Heapify(size, largest);
	}
}
