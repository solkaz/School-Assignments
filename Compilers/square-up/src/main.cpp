#include "sub_square.hpp"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

using SubSquareList = std::vector<SubSquare>;

SubSquareList CarveEvenSuperSquare(int);
SubSquareList Solve(int);
void PrintSubSquareList(SubSquareList);
int IsPrime(int);
SubSquareList CarveEvenIRBottomRight(int);
SubSquareList CarveOddIRBottomRight(int);
SubSquareList SolveIR(int);
SubSquareList SolvePrime(int);
SubSquareList CarveOddSuperSquareSection(int);
SubSquareList Concatenate(SubSquareList, SubSquareList);
SubSquareList SolveIIR(int);
int ComputeIIRSquares(int, int);
SubSquareList IIRSquaresPlacement(int, int);
    
int main(int argc, char *argv[]) {

    try {

	// // Check that the size arg was inputted
	// if (argv[1] == nullptr) {
	//     throw std::logic_error("Missing size N argument");
	// }

	// Convert the size arg from std::string to int
	auto n = std::stoi(argv[1]);

	// Squares of size 1 cannot be solved; throw an error if it was inputted
	if (n == 1) {
	    throw std::invalid_argument("N must be > 1");
	}

	// Get the list of squares
	auto squares = Solve(n);
	// Print the list of squares out
	PrintSubSquareList(squares);

	
    } catch (const std::invalid_argument &err) {
	// Catch exceptions, output their error message, and exit the program
	std::cout << err.what() << std::endl;
	return 1;
    } catch (const std::logic_error &err) {
	std::cout << "Missing size N argument" << std::endl;
	return 1;
    }
    return 0;
}

// Compute the "half-size" of a region, which is the ceiling of size / 2
int HalfSize(int size) {
    // std::ceil will return a float, so we need to static cast it
    // back to an int
    return static_cast<int>(
	// size needs to be converted to a float to divide properly
	std::ceil(static_cast<float>(size) / 2.0)
	);
}

// Carve the squares for an even-sized super square
SubSquareList CarveEvenSuperSquare(int size) {
    SubSquareList squares;

    // Each of the sub-squares will be half the length of the outer square
    auto sub_square_size = size / 2;

    // Carve the sub-squares out
    for (int i = 0; i < 4; ++i) {
	int x = (i % 2 == 0 ? 0 : sub_square_size);
	int y = (i > 1 ? sub_square_size : 0);
	squares.emplace_back(sub_square_size, x, y);
    }
    // Return the list of squares
    return squares;
}

SubSquareList Solve(int size) {

    // Easy case is if the size is even; we carve 4 equal-sized squares
    if (size % 2 == 0) {
	auto even_squares = CarveEvenSuperSquare(size);
	return even_squares;
    } else {

	// Check if the size is a prime number
	auto divisor = IsPrime(size);

	// Size is prime
	if (divisor == -1) {
	    auto squares = SolvePrime(size);
	    return squares;
	} else {

	    // Since it's not prime, we can take the divisor's result
	    // and scale the square's out
	    auto divisor_squares = Solve(divisor);

	    // # to multiply each side length & position by
	    auto multiplier = size / divisor;

	    // Scale each of the squares
	    for (auto &i : divisor_squares) {
		i.Scale(multiplier);
	    }
	    // Return the list of squares
	    return divisor_squares;
	}
    }
}

// Method to print the length & sub-square's info
void PrintSubSquareList(SubSquareList s) {
    // Print the # of sub-squares
    std::cout << s.size() << std::endl;
    // Print the sub-squares' info
    for (auto &i : s) {
	std::cout << i.to_str() << std::endl;
    }
}

int IsPrime(int n) {
    // Check if n is prime

    // Check divisors of n up to square_root
    auto square_root = static_cast<int>(std::sqrt(static_cast<float>(n)));
    // Increment by two because even numbers cannot divide odd numbers
    for (int i = 3; i <= square_root; i += 2) {
	// Return the divisor if it can divide n
	if (n % i == 0) {
	    return i;
	}
    }
    // Return -1 if prime
    return -1;
}

SubSquareList CarveOddSuperSquareSection(int half_size) {
    SubSquareList squares;

    // Carve a square from the top left corner of the super square
    // Its size will be == to the half-size of the super square
    squares.emplace_back(half_size, 0, 0);

    // Carve two squares with side len. == (half-size - 1)
    // These squares will be immediately to the right and below the
    // square carved above
    
    // To the right
    squares.emplace_back(half_size - 1, half_size, 0);
    // Below
    squares.emplace_back(half_size - 1, 0, half_size);

    return squares;
}

SubSquareList SolvePrime(int size) {
    // First get the half-size, which is the ceiling of half of the size
    auto half_size = HalfSize(size);

    // Carve a section
    auto top_left = CarveOddSuperSquareSection(half_size);

    // Solve the Irregular region
    auto IR_list = SolveIR(half_size);

    // Add an offset for the subsquares from SolveIR
    for (auto &i : IR_list) {
	i.AddOffset(half_size - 1);
    }

    // Combine the SubSquareLists
    auto combined = Concatenate(IR_list, top_left);
    return combined;
}

SubSquareList CarveEvenIRBottomRight(int quarter_size) {
    SubSquareList squares;

    squares.emplace_back(quarter_size, quarter_size, quarter_size);
    squares.emplace_back(quarter_size, quarter_size, 0);
    squares.emplace_back(quarter_size, 0, quarter_size);

    return squares;
}

SubSquareList CarveOddIRBottomRight(int quarter_size) {
    // Carve the bottom three squares in the IR
    
    SubSquareList squares;
    squares.emplace_back(quarter_size, quarter_size - 1, quarter_size - 1);
    squares.emplace_back(quarter_size - 1, quarter_size, 0);
    squares.emplace_back(quarter_size - 1, 0, quarter_size);
    // Return the subsquares
    return squares;
}

SubSquareList SolveIR(int half_size) {
    SubSquareList squares;
    // Base case (if IR size == 3)
    if (half_size == 2) {
	squares.emplace_back(1, 1, 0);
	squares.emplace_back(1, 0, 1);
	squares.emplace_back(1, 1, 1);

	return squares;
    } else if (half_size % 2 == 0) {
	// Half size is even
	auto quarter_size = HalfSize(half_size);
	auto bottom_right = CarveEvenIRBottomRight(quarter_size);

	auto top_left = SolveIR(quarter_size);

	auto combined = Concatenate(top_left, bottom_right);

	return combined;
	
    } else {
	auto quarter_size = HalfSize(half_size);
	auto bottom_right = CarveOddIRBottomRight(quarter_size);

	auto top_left = SolveIIR(quarter_size);

	auto combined = Concatenate(top_left, bottom_right);

	return combined;
    }
}

SubSquareList SolveIIR(int quarter_size) {
    int min_result = -1;
    int min_gap = 0;
    int boundary = static_cast<int>(
	std::floor(static_cast<float>(quarter_size) / 2.0)
	);
    int gap = 0;
    for (; gap < boundary; ++gap) {
	int result = ComputeIIRSquares(quarter_size, gap);

	if (min_result == -1 || result < min_result) {
	    min_result = result;
	    min_gap = gap;
	} else {
	    break;
	}
    }
    auto IIR_squares = IIRSquaresPlacement(quarter_size, min_gap);
    return IIR_squares;
}

int ComputeIIRSquares(int size, int gap) {
    int square_count = 1;
    int top_right_square_len = size - 1 - gap;
    
    int barrier_squares_len = gap + 1;

    int barrier_len = size - 1;

    if (barrier_len % barrier_squares_len == 0) {
	square_count += ((barrier_len / barrier_squares_len) * 2 - 1);
	square_count += gap * 2;
    } else {
	square_count += (
	    static_cast<int>(
		std::floor(static_cast<float>(barrier_len) /
			   static_cast<float>(barrier_squares_len))
		) * 2 - 1
	    );
	square_count += (barrier_len % barrier_squares_len) * barrier_squares_len * 2;
	square_count += gap * 2;
    }

    return square_count;
}

SubSquareList IIRSquaresPlacement(int size, int gap) {
    SubSquareList squares;
    
    int top_right_square_len = size - 1 - gap;
    int barrier_squares_len = gap + 1;
    // Carve the top right square in the IIR
    squares.emplace_back(top_right_square_len,
			 size - top_right_square_len,
			 0);
    // Number of barrier squares to add
    auto num_of_barrier_squares = (
	static_cast<int>(
	    std::floor(static_cast<float>(size - 1) /
		       static_cast<float>(barrier_squares_len))
	    ) * 2 - 1
	);

    // Carve the barrier squares

    // Calculate the # of barrier squares to carve in each direction
    auto num_of_verticals = static_cast<int>(
	std::ceil(static_cast<float>(num_of_barrier_squares) / 2.0)
	);
    auto num_of_horizontals = num_of_verticals - 1;

    // Set the positions of the vertical barrier squares
    auto x_pos = 0;
    auto y_pos = size - barrier_squares_len;
    // Carve the vertical squares
    for (int i = 0; i < num_of_verticals; ++i) {
	squares.emplace_back(barrier_squares_len,
			     x_pos,
			     y_pos);
	y_pos -= barrier_squares_len;
    }

    // Set the positions of the horizontal barrier squares
    x_pos = barrier_squares_len;
    y_pos = size - barrier_squares_len;

    // Carve the horizontal squares
    for (int i = 0; i < num_of_horizontals; ++i) {
	squares.emplace_back(barrier_squares_len,
			     x_pos,
			     y_pos);
	x_pos += barrier_squares_len;	
    }

    // Add the gap squares if there were any
    if (gap) {
	squares.emplace_back(1, 1, 0);
	squares.emplace_back(1, size - 1, size - 2);
    }

    // Return the list of squares
    return squares;
}

SubSquareList Concatenate(SubSquareList a, SubSquareList b) {
    // Create a new SubSquareList that is a concatenation of a and b
    std::copy(a.begin(), a.end(), std::back_inserter(b));
    return b;
}
