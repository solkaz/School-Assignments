#ifndef SQUARE_GROUP_HPP_
#define SQUARE_GROUP_HPP_

#include "sub_square.hpp"

#include <vector>

using SubSquareList = std::vector<SubSquare>;

class SquareGroup {

    int count_;
    SubSquareList squares_;

public:
    
    SquareGroup();
    SquareGroup(int);

    SquareGroup(SubSquareList&);

    void EmplaceBack(int, int, int);

    void AddSubSquares(SubSquareList);
    
    void Print() const;
};

#endif // SQUARE_GROUP_HPP_
