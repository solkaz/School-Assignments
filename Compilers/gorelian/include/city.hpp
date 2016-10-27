#ifndef CITIES_HPP_
#define CITIES_HPP_

#include <array>
#include <limits>
#include <vector>

enum Direction { NORTH, EAST, SOUTH, WEST };

struct Intersection {
    // Speed limits 
    std::array<int, 4> speed_limits_;
    // # of blips to travel to intersection
    int blips_;

    Intersection () {
	// Speed limit in all directions default to 0
	std::fill(speed_limits_.begin(), speed_limits_.end(), 0);
	// Set the blips to the max int (for initial comparisons)
	blips_ = std::numeric_limits<int>::max();
    }
};

using IntersectionCol = std::vector<Intersection>;
using IntersectionGrid = std::vector<IntersectionCol>;

class CityGrid {
    IntersectionGrid intersects_;
    // # of horizontal & vertical blocks respectively
    int horz_blocks_;
    int vert_blocks_;

    void ReadHorizontalSpeedLimits(int);
    void ReadVerticalSpeedLimits(int);
    
public:
    CityGrid() : CityGrid(1, 1) {}
    CityGrid(unsigned int, unsigned int);

    void ReadSpeedLimits();

    int ShortestPath();
};

#endif // CITIES_HPP_
