#include "square_group.hpp"

SquareGroup::SquareGroup() {
    count_ = 0;
    squares_.clear();
}

SquareGroup::SquareGroup(int n) {
    count_ = n;
    squares_.resize(n);
}

SquareGroup::SquareGroup(std::vector<InnerSquare> &squares) {
    squares_ = squares;
    count_ = squares_.size();
}

void SquareGroup::EmplaceBack(int square_size, int x, int y) {

    // Construct a new element in the back of the container
    squares_.emplace_back(square_size, x, y);
    
    // Increment the count
    ++count_;
}
