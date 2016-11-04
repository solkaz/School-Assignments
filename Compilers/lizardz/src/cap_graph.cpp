#include "cap_graph.hpp"

#include <algorithm>
#include <queue>
#include <set>
#include <iostream>

int DistanceBetweenPillars(int y1, int x1, int y2, int x2) {
    // Calculate the distance between two pillars
    // Not the "true" distance because we don't take the sq. root
    // But it is compared to max_leap_dist ^ 2, making it correct
    int dx = x2 - x1, dy = y2 - y1;
    return dx * dx + dy * dy;
}

FlowGraph::FlowGraph(PillarMap pillars, LizardMap lizards, int num_rows,
		     int max_leap_dist) : num_rows_(num_rows),
					  num_cols_(pillars[0].size()),
					  num_lizards_(0) {
    // Number of "nodes"; each pillar will have an "in" and "out" node, and
    // there exist two special nodes: SOURCE and SINK, which are 0 and 1 respectively
    num_nodes_ = num_rows_ * num_cols_ * 2 + 2;
    capacities_.resize(num_nodes_, PillarMapCol(num_nodes_, 0));

    for (int row = 0; row < num_rows_; ++row) {
	for (int col = 0; col < num_cols_; ++col) {
	    // Calculate the in/out node indexes for each pillar
	    auto IO_indexes = MakeInOutIndexes(row, col);
	    // Connect the in nodes to their respective out nodes
	    capacities_[IO_indexes.first][IO_indexes.second] = pillars[row][col];

	    // Connect each lizard to the source node
	    if (lizards[row][col] == 'L') {
		capacities_[SOURCE][IO_indexes.first] = 1;
		++num_lizards_;
	    }
	    // If the edge can be leapt to by a pillar, connect that pillar
	    // to the sink
	    if (row < max_leap_dist || row > num_rows_ - max_leap_dist - 1 ||
		col < max_leap_dist || col > num_cols_ - max_leap_dist - 1) {
		capacities_[IO_indexes.second][SINK] = INFINITY;
	    }

	    // If there exist any pillars that can be leapt to, the row values
	    // will be guaranteed be within row +/- the leap distance (and
	    // within the grid boundaries)
	    int srch_row_start = (row - max_leap_dist > 0 ?
				  row - max_leap_dist : 0);
	    int srch_row_end = (row + max_leap_dist < num_rows_ ?
				row + max_leap_dist : num_rows_);
	    int srch_col_start = (col - max_leap_dist > 0 ?
				  col - max_leap_dist : 0);
	    int srch_col_end = (col + max_leap_dist < num_cols_ ?
				col + max_leap_dist : num_cols_);

	    int squared_max_leap_dist = max_leap_dist * max_leap_dist;

	    // Search for pillars that can be leapt to within the range specified by
	    // the srch_* variables
	    for (int srch_row = srch_row_start; srch_row < srch_row_end; ++srch_row) {
		for (int srch_col = srch_col_start; srch_col < srch_col_end; ++srch_col) {
		    // Connect all pillars that are within the max_leap_dist
		    if ((row != srch_row || col != srch_col) &&
			(DistanceBetweenPillars(row, col, srch_row, srch_col) <=
			 squared_max_leap_dist)) {
			capacities_[IO_indexes.second][MakeInIndex(srch_row, srch_col)] = INFINITY;
		    }
		}
	    }
	}
    }
}

int FlowGraph::GetSaveableLizards() {
    std::vector<std::vector<int>> flow (num_nodes_, std::vector<int>(num_nodes_, 0));

    // Do nothing will there are still paths to process
    while (Flush(flow) > 0) {}

    // Get the sum of lizards that could get to safety
    int num_saved_lizards = std::accumulate(flow[SOURCE].cbegin(), flow[SOURCE].cend(), 0);

    // Return the # of safe lizards
    return num_saved_lizards;
}

int FlowGraph::Flush(std::vector<std::vector<int>> &flow) {

    // Queue of node indexes to visit
    std::queue<int> nodes_to_visit;
    // First node to visit will be SOURCE
    nodes_to_visit.push(SOURCE);

    // Set of visited nodes
    std::set<int> visited_nodes;
    // SOURCE is the only such node so far
    visited_nodes.insert(SOURCE);

    // list of the "parent" (previous) node for each node 
    std::vector<int> parent_node(num_nodes_, -1);

    // Keep going while there are still nodes to visit
    while (!nodes_to_visit.empty()) {
	int curr_node = nodes_to_visit.front();
	nodes_to_visit.pop();

	if (curr_node == SINK) {
	    // Number of lizards that can go through this path
	    int flow_amt = INFINITY;

	    // Start at the sink
	    int n = curr_node;
	    // Find the bottleneck from the sink to the source
	    while (n != SOURCE) {
		flow_amt = std::min(flow_amt, capacities_[parent_node[n]][n] - flow[parent_node[n]][n]);
		n = parent_node[n]; // Examine n's parent node
	    }

	    // Go back to the sink
	    n = curr_node;
	    while (n != SOURCE) {
		// add the # of lizards that can go from parent_node[n] -> n
		flow[parent_node[n]][n] += flow_amt;
		// remove the # of lizards that can go from n -> parent_node[n]
		flow[n][parent_node[n]] -= flow_amt;
		// Switch to n's parent node
		n = parent_node[n];
	    }
	    // Return the amount of lizards that can get out through this path
	    return flow_amt;
	}

	for (int v = 0; v < num_nodes_; ++v) {
	    // Add this node if it can support transporting lizards and it
	    // hasn't already been seen/visited
	    if (capacities_[curr_node][v] - flow[curr_node][v] > 0 &&
		!(visited_nodes.find(v) != visited_nodes.end())) {
		
		nodes_to_visit.push(v);
		visited_nodes.insert(v);
		// set the parent node of curr_node
		parent_node[v] = curr_node;
	    }
	}
    }

    // All paths have been processed
    return 0;
}

int FlowGraph::GetDoomed() {
    // Return the # of doomed lizards AKA the # of lizards to start
    // minus the max flow capacity (how many lizards are able to get to safety)
    return num_lizards_ - GetSaveableLizards();
}
