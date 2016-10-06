#ifndef SUB_SQUARE_HPP_
#define SUB_SQUARE_HPP_

#include <string>

struct SubSquare {
    SubSquare(): side_length_(0), x_(0), y_(0) {}
    SubSquare(int side_length, int x, int y):
	side_length_(side_length), x_(x), y_(y) {}
    int side_length_;
    int x_, y_;

    void Scale(int n) {
    	x_ *= n;
    	y_ *= n;
    	side_length_ *= n;
    }

    std::string to_str() const {
	return (
	    std::to_string(side_length_) + ' ' +
	    std::to_string(x_) + ' ' +
	    std::to_string(y_)
	    );
    }
};

#endif // SUB_SQUARE_HPP_
