#include "square_group.hpp"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

std::vector<SubSquareList> memoized_squares;

int main(int argc, char *argv[]) {

    try {
	if (argv[1] == nullptr) {
	    throw std::logic_error("Missing size N argument");
	}
	
	auto n = std::stoi(argv[1]);

	if (n > 20 || n <= 1) {
	    throw std::invalid_argument("N must be between 1 and 20 inclusive");
	}

	std::cout << "Valid integer N inputted: " << n << std::endl;

	Solve(n);
	
    } catch (const std::invalid_argument &err) {
	std::cout << err.what() << std::endl;
	return 1;
    } catch (const std::logic_error &err) {
	std::cout << err.what() << std::endl;
	return 1;
    }
    
    return 0;
}

SubSquareList CarveEvenSuperSquare(int size) {

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

SubSquareList CarveTopLeftSection(int half_size) {
    SubSquareList squares;

    // Carve the top left corner with the largest sub_square, with the side
    // length being the half_size (AKA the ceiling of (n/2))
    squares.emplace_back(half_size, 0, 0);

    // We'll then carve the next two largest squares, which will have a side
    // length of half_size - 1, or one less than the largest square. They will
    // take up the top right and bottom left corner of the super-square
    auto sub_squares_size = half_size - 1;

    // These squares will be placed on the larger square's bounds on both
    // axes. 
    squares.emplace_back(sub_square_size, half_size, 0);
    squares.emplace_back(sub_square_size, 0, half_size);

    return squares;
}

SubSquareList Solve(int size) {

    // 
    SubSquareList squares;

    
    if (size % 2 == 0) {
	squares = CarveEvenSuperSquare(size);
    } else {

	auto divisor = IsPrime(size);
	// Prime
	if (divisor == -1) {
	    
	} else {
	    if (memoized_squares[divisor].empty()) {
		Solve(divisor);
	    } else {
		auto foo = memoized_squares[divisor];

		auto multiplier = size / divisor;
		
		std::transform(foo.begin(), foo.end(), foo.begin(),
			       [multiplier](SubSquare s) { s.Scale(multiplier); })
	    }
	}
	
	// Calculate the 'half-size' of the super-square
	auto half_size = half_super_square_size(size);
	
	// Carve out a section from the top left half of the board
	CarveTopLeftSection(half_size);
	
	// We're now left with a region in the bottom right that is a square of the
	// same size as the larger sub-square in the top left, but with a 1x1
	// square removed from the top. We'll call it the Irregular Region,
	// or simply IR. We now want to find the minimum of squares needed in this
	// region of the super-square
	
	// half_size is inputted because
	SolveIR(half_size);
    }
}

SubSquareList SolveIR(int size) {
    // First run a parity check on the IR's size, just as if we were solving a
    // normal square. This is because we follow the same strategies as before,
    // but with a few extra steps

    // Even size means that we can carve for 
    if (size % 2 == 0) {
	// 
	auto IR_sub_squares = CarveEvenIRSubSquares(size);
	// We'll now be left with a sub-IR in the top left corner of the IR
	// So we can recursively solve that region by inputting half of the
	// super-IR's size
	auto sub_IR_squares = SolveIR(size / 2);
	
    } else {
	
    }
}

SubSquareList CarveEvenIRSubSquares(int size) {

    SubSquareList squares;
    // Side lengths of the three sub-squares
    auto sub_square_size = size / 2;
    // These 
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

SubSquareList CarveOddIRSubSquares(int size) {
    
}

SubSquareList ConcatSubSquareLists(SubSquareList first, SubSquareList second) {
    SubSquareList new_list(0);
    std::copy(first.begin(), first.end(), std::back_inserter(new_list));
    std::copy(second.begin(), second.end(), std::back_inserter(new_list));

    return new_list;
}

