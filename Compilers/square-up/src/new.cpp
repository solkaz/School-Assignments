#include "sub_square.hpp"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

using SubSquareList = std::vector<SubSquare>;
std::vector<SubSquareList> memoized_squares;

SubSquareList CarveEvenSuperSquare(int);
SubSquareList Solve(int);
void PrintSubSquareList(SubSquareList);
int IsPrime(int);
void AddBaseSquares();

int main(int argc, char *argv[]) {

    try {
	if (argv[1] == nullptr) {
	    throw std::logic_error("Missing size N argument");
	}
	
	auto n = std::stoi(argv[1]);

	std::cout << "Valid integer N inputted: " << n << std::endl;

	AddBaseSquares();
	
	auto squares = Solve(n);
	PrintSubSquareList(squares);
	
    } catch (const std::invalid_argument &err) {
	std::cout << err.what() << std::endl;
	return 1;
    } catch (const std::logic_error &err) {
	std::cout << err.what() << std::endl;
	return 1;
    }
    return 0;
}

void AddBaseSquares() {
    memoized_squares.resize(3);
    SubSquareList three;
    three.emplace_back(2, 0, 0);
    three.emplace_back(1, 2, 0);
    three.emplace_back(1, 2, 1);
    three.emplace_back(1, 2, 2);
    three.emplace_back(1, 1, 2);
    three.emplace_back(1, 0, 2);
    memoized_squares[2] = three;
}

SubSquareList CarveEvenSuperSquare(int size) {

    SubSquareList squares;

    // Each of the sub-squares will be half the length of the outer square
    auto sub_square_size = size / 2;

    for (int i = 0; i < 4; ++i) {
	int x = (i % 2 == 0 ? 0 : sub_square_size);
	int y = (i > 1 ? sub_square_size : 0);
	    
	squares.emplace_back(sub_square_size, x, y);
    }
    return squares;
}

SubSquareList Solve(int size) {

    if (size % 2 == 0) {
	auto even_squares = CarveEvenSuperSquare(size);
	return even_squares;
    } else {
	auto divisor = IsPrime(size);
	if (divisor == -1) {
	    
	} else {
	    if (memoized_squares[divisor - 1].empty()) {
		// Solve for the divisor
	    } else {
		auto divisor_squares = memoized_squares[divisor - 1];

		auto multiplier = size / divisor;

		for (auto &i : divisor_squares) {
		    i.Scale(multiplier);
		}
		
		return divisor_squares;
	    }
	}
    }
    return SubSquareList();
}

void PrintSubSquareList(SubSquareList s) {
    std::cout << s.size() << std::endl;
    for (auto &i : s) {
	std::cout << i.to_str() << std::endl;
    }
}

int IsPrime(int n) {
    auto square_root = static_cast<int>(std::sqrt(static_cast<float>(n)));
    for (int i = 3; i <= square_root; i += 2) {
	if (n % i == 0) {
	    return i;
	}
    }
    // Return -1 if prime
    return -1;
}
