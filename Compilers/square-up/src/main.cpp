#include "square_group.hpp"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

std::vector<unsigned long long> memoized_squares;

int main(int argc, char *argv[]) {

    try {
	if (argv[1] == nullptr) {
	    throw std::logic_error("Missing size N argument");
	}
	
	auto n = std::stoi(argv[1]);

	if (n > 20 || n <= 1) {
	    throw std::invalid_argument("N must be (1, 20]");
	}

	std::cout << "Valid integer N inputted: " << n << std::endl;
	
    } catch (const std::invalid_argument &err) {
	std::cout << err.what() << std::endl;
	return 1;
    } catch (const std::logic_error &err) {
	std::cout << err.what() << std::endl;
	return 1;
    }

    memoized_squares.clear();
    
    return 0;
}

SubSquareList split_even_square(int size) {

    SubSquareList squares;

    // Each of the sub-squares will be half the length of the outer square
    auto sub_square_size = size / 2;

    for (int i = 0; i < 4; ++i) {
	int x = (i % 2 == 0 ? 0 : mini_square_size);
	int y = (i > 1 ? mini_square_size : 0);
	    
	squares.emplace_back(mini_square_size, x, y);
    }
    return squares;
}

int half_super_square_size(int size) {
    // std::ceil will return a float; thus we convert the result
    // back to an int
    return static_cast<int>(
	std::ceil(static_cast<float>(n) / 2.0)
	);
}

SubSquare carve_biggest_square(int size) {
    // Compute the subsquare's side length



    return SubSquare(sub_square_size);
}

SubSquareList carve_second_biggest_squares(int size) {
    SubSquareList squares;

    auto largest_size = half_super_square_size(size);
    auto sub_square_size = largest_size - 1;

    squares.emplace_back(sub_square_size, largest_size, 0);
    squares.emplace_back(sub_square_size, 0, largest_size);

    return squares;
}

SquareGroup solve_square(int size) {

    // 
    SubSquareList squares;

    
    if (size % 2 == 0) {
	squares = split_even_square(size);
    } else {
	// Calculate the 'half-size' of the super-square
	auto half_size = half_super_square_size(size);
	
	// First carve the biggest square from the 
	auto largest_sub_square = carve_biggest_square(size);
	squares.push_back(largest_sub_square);
	
	// Then carve two squares with side length (largest_square_size - 1)
	// These will be placed above and to the right of the largest squrae

	auto second_largest_sub_squares = carve_second_biggest_squares(size);

	// Extend the SubSquareList to include the 2nd largest sub-squares
	std::copy(second_largest_sub_squares.begin(),
		  second_largest_sub_squares.end(),
		  std::back_iterator(squares)
	    )
	
	// After these three squares, we're left with a square with the same
	// side length as the largest square, but with a 1x1 square removed
	// from the top left. We can find the min. number of squares in this
	// region by 

	// 
	if (largest_square_len % 2 == 0) {
	    // Create the three "normal" squares
	    
	    auto incomplete_sq_mini_len = largest_square_len / 2;


	} else {
	    
	}
    }
}

SubSquareList solve_IR(int size) {
    // 
    if (size % 2 == 0) {
	// Check that
	
    } else {
	
    }
}

SubSquareList carve_even_IR_sub_squares(int size) {

    SubSquareList squares;
    auto sub_square_size = size / 2;
    auto placement = size - 1 + sub_square_size;
    // Top right
    squares.emplace_back(
	sub_square_size,
	placement,
	size - 1,
	);

    // Bottom left
    squares.emplace_back(
	sub_square_size,
	size - 1,
	placement
	);

    // Bottom right
    squares.emplace_back(
	sub_square_size,
	placement,
	placement
	);
    return squares;
}

SubSquareList ExtendSubSquareList(SubSquareList source, SubSquareList dest) {
    
}
