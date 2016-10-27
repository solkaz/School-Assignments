#include "new_city.hpp"

#include <iostream>

int main() {
    int num_blocks_hor, num_blocks_vert;

    // Read in the # of horizontal and vertical blocks, respectively
    std::cin >> num_blocks_hor >> num_blocks_vert;

    // Continue to read input while num_blocks_hor & num_blocks_vert != 0
    while (num_blocks_hor && num_blocks_vert) {
	// Create a CityGrid from the inputted dimensions
	CityGrid grid(num_blocks_vert, num_blocks_hor);
	// Read the speed limits in
	grid.ReadSpeedLimits();
	// Get the fastest route
	auto shortest_path = grid.ShortestPath();
	// Print the result if shortest_path != int max; AKA if it is reachable
	if (shortest_path != std::numeric_limits<int>::max()) {
	    std::cout << shortest_path << " blips" << std::endl;
	} else {
	    std::cout << "Holiday" << std::endl;
	}
	// Get another input
	std::cin >> num_blocks_hor >> num_blocks_vert;
    }
}


