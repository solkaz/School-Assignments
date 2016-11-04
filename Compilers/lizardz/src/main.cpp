#include "cap_graph.hpp"

#include <iostream>
#include <string>
#include <vector>

using GridDimensions = std::pair<int, int>;

void PrintCase(int iteration, int doomed_lizards) {
    std::cout << "Case #" << iteration << ": ";

    // Print the results (with correct grammar)
    if (doomed_lizards < 2) {
	std::cout << (doomed_lizards ? "1" : "No") << " lizard was left behind";
    } else {
	std::cout << doomed_lizards << " lizards were left behind";
    }
    std::cout << std::endl;
}

PillarMap ReadPillarInput(int num_rows) {
    PillarMap grid(num_rows);
    
    std::string input_row;
    
    for (int row = 0; row < num_rows; ++row) {
	// Read input one row at a time
	std::cin >> input_row;
	// Iterate through all characters and construct 
	for (const auto &c : input_row) {
	    grid[row].emplace_back(static_cast<int>(c - '0'));
	}
    }
    return grid;
}

LizardMap ReadLizards(int num_rows) {
    LizardMap lizard_map (num_rows);

    // Read the inputted # of rows, which contain the positions of the
    // lizards
    for (int row = 0; row < num_rows; ++row) {
	std::cin >> lizard_map[row];
    }
    // Return the whole lizard map
    return lizard_map;
}

int main() {

    // Read the # of test cases in
    int num_test_cases; std::cin >> num_test_cases;

    // Process each test case
    for (int test_iter = 0; test_iter < num_test_cases; ++test_iter) {
	// Get the # of rows this test case contains and the maximum leaping
	// distance that a lizard can leap for this test case
	int num_rows, max_leap_dist;
	std::cin >> num_rows >> max_leap_dist;

	// Get the positions of the pillars and lizards 
	auto pillar_map = ReadPillarInput(num_rows);
	auto lizard_map = ReadLizards(num_rows);

	FlowGraph flow_graph(pillar_map, lizard_map, num_rows, max_leap_dist);

	// Get the # of doomed lizards
	int doomed_lizards = flow_graph.GetDoomed();

	// Print the result of this test case
	PrintCase(test_iter, doomed_lizards);
    }

    return 0;
}
