#include "Sort Visualizer/Sort Visualizer.h"

int main() {
	sort::SortVisualizer visual{ 1280, 720, 0, 100, 0, SortObject::SELECTION_SORT };
	visual.Init();
	visual.run();
	return 0;
}