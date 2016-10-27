#include "new_city.hpp"

#include <iostream>
#include <limits>
#include <queue>
#include <utility>

using DistTableCol = std::vector<int>;
using DistTable = std::vector<DistTableCol>;
using GridPos = std::pair<int, int>;

struct GridPosPair {
    GridPos pos_;
    int blips_to_pos_;

    GridPosPair(GridPos pos, int blips) : pos_(pos), blips_to_pos_(blips) {}
};

// Comparator function for the priority_queue
auto comparator = [](const GridPosPair &a, const GridPosPair &b)
{ return a.blips_to_pos_ > b.blips_to_pos_; };

using UnvisitedSet = std::priority_queue<GridPosPair,
					 std::vector<GridPosPair>,
					 decltype(comparator)>;

CityGrid::CityGrid(unsigned int v, unsigned int h) {
    horz_blocks_ = h; vert_blocks_ = v;
    intersects_ = IntersectionGrid(v + 1, IntersectionCol(h + 1));
}

void CityGrid::ReadSpeedLimits() {
    /* Reading the speed limits for each intersection requires reading in 
     * the speed limits going in both horizontal and vertical directions
     */

    for (int i = 0; i < vert_blocks_ + 1; ++i) {
	// Read in the horizontal speed limits for the street
	ReadHorizontalSpeedLimits(i);

	// Don't read vertical speed limits for the last row of intersections
	if (i != vert_blocks_) {
	    ReadVerticalSpeedLimits(i);
	}
    }
}

void CityGrid::ReadHorizontalSpeedLimits(int row) {
    int speed; char dir;
    
    for (int i = 0; i < horz_blocks_; ++i) {
	// read in the speed limit and the directional char
	std::cin >> speed >> dir;
	
	// Apply the speed limits to the directions as specified by the
	// direction character
	switch (dir) {
	    case '*': {
		// Two-way street
		intersects_[row][i].speed_limits_[EAST] = speed;
		intersects_[row][i + 1].speed_limits_[WEST] = speed;
		break;
	    }
	    case '<': {
		// One-way street going west
		intersects_[row][i + 1].speed_limits_[WEST] = speed;
		break;
	    }
	    case '>': {
		// One-way street going east
		intersects_[row][i].speed_limits_[EAST] = speed;
		break;
	    }
	}
    }
}

void CityGrid::ReadVerticalSpeedLimits(int row) {
    int speed; char dir;

    // Need to read +1 more because the # of vertically aligned streets =
    // horz_blocks_ + 1
    for (int i = 0; i < horz_blocks_ + 1; ++i) {
	// read in the speed limit and the directional char
	std::cin >> speed >> dir;

	// Apply the speed limits to the directions as specified by the
	// direction character
	switch (dir) {
	    case '*': {
		// Street is two-way
		intersects_[row][i].speed_limits_[SOUTH] = speed;
		intersects_[row + 1][i].speed_limits_[NORTH] = speed;
		break;
	    }
	    case '^': {
		// Street is one-way going northward
		intersects_[row + 1][i].speed_limits_[NORTH] = speed;
		break;
	    }
	    case 'v': {
		// Street is one-way going southward
		intersects_[row][i].speed_limits_[SOUTH] = speed;
		break;
	    }
	}
    }
}




int CityGrid::ShortestPath() {
    // Implementation of Dijkstra's algorithm

    // Set the starting node's blip distance to 0
    intersects_[0][0].blips_ = 0;

    // Start with the Gorelian housing intersection (0,0)
    UnvisitedSet to_visit (comparator);
    to_visit.emplace(GridPos(0,0), 0);

    // Continue while all visitable nodes haven't been visited
    while (!to_visit.empty()) {
	// Get the Intersection that has the shortest distance from the
	// Gorelian housing
	auto opt_vert = to_visit.top();
	// Remove the Intersection
	to_visit.pop();

	// Coordinates of the intersection that's being visited
	int opt_vert_col = opt_vert.pos_.first;
	int opt_vert_row = opt_vert.pos_.second;

	// Speed limits coming from this intersection
	auto speed_limits = intersects_[opt_vert_row][opt_vert_col].speed_limits_;
	
	// Check in all 4 directions
	for (int i = NORTH; i < WEST; ++i) {
	    int speed_limit = speed_limits[i];

	    // If the speed limit is 0 for any direction, then that road cannot
	    // traversed that way, and thus that direction is skipped over
	    if (!speed_limit) {
		continue;
	    }

	    // Calculate the # of blips it would take to traverse this block
	    int blips = 2520 / speed_limit;

	    // Blip-time to get to the corresponding Intersection
	    // through this intersection
	    auto tentative_blips = intersects_[opt_vert_row][opt_vert_col].blips_ + blips;
	    
	    // Depending on the direction that we're checking, we'll add an x/y
	    // modifier to get the relevant Intersection from intersects_
	    // We check that we're not at a boundary before we add/subtract the mod
	    int test_vert_row = opt_vert_row;
	    int test_vert_col = opt_vert_col;
	    switch (i) {
		case NORTH: {
		    if (opt_vert_row > 0) {
			test_vert_row -= 1;
		    }
		    break;
		}
		case EAST: {
		    if (opt_vert_col < horz_blocks_) {
			test_vert_col += 1;
		    }
		    break;
		}
		case SOUTH: {
		    if (opt_vert_row < vert_blocks_) {
			test_vert_row += 1;
		    }
		    break;
		}
		case WEST: {
		    if (opt_vert_col > 0) {
			test_vert_col -= 1;
		    }
		    break;
		}
	    }

	    // Get the currently "shortest" blip-time to get to this intersection
	    auto curr_best_blips = intersects_[test_vert_row][test_vert_col].blips_;

	    // Compare the two times; keep the smaller of the two
	    if (tentative_blips < curr_best_blips) {
		// Replace the blip-time
		intersects_[test_vert_row][test_vert_col].blips_ = tentative_blips;
		// Add the intersection to be visited
		to_visit.emplace(GridPos(test_vert_col, test_vert_row), tentative_blips);
	    }
	}
    }

    // Return the distance from Gorelian Housing to the Govt building
    return intersects_[vert_blocks_][horz_blocks_].blips_;
}

