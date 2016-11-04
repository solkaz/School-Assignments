#ifndef CAP_GRAPH_HPP_
#define CAP_GRAPH_HPP_

#include "types.hpp"

#include <limits>

const int INFINITY = std::numeric_limits<int>::max();
constexpr int SOURCE = 0;
constexpr int SINK = 1;

class FlowGraph {
    int num_lizards_;
    int num_rows_;
    int num_cols_;
    int num_nodes_;
    PillarMap capacities_;

    int MakeInIndex(int row, int col) {
	return (row * num_cols_ + col) * 2 + 2;
    }
    InOutPair MakeInOutIndexes(int row, int col) {
	int in = MakeInIndex(row, col);
	return std::make_pair(in, in + 1);
    }
    
public:
    FlowGraph(PillarMap, LizardMap, int, int);
    int GetSaveableLizards();
    int Flush(std::vector<std::vector<int>>&);
    int GetDoomed();
};

#endif // CAP_GRAPH_HPP_
