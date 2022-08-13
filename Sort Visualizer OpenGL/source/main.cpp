#include <iostream>

#include "Sort Visualizer/Sort Visualizer.h"

int main(int argc, char* argv[]) {
	if (argc <= 6) {
		std::cout << "Not enough arguments. Example:\n1.Screen width\n2.Screen height\n3.First element\n4.Last element\n5.Speed of execution\n6.Sort type";
		return 1;
	}
	sort::SortVisualizer visual{ argv[1], argv[2], argv[3], argv[4], argv[5], argv[6] };
	visual.Init();
	visual.run();
	return 0;
}