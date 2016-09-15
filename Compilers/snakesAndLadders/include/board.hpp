#ifndef INCLUDE_BOARD_HPP_
#define INCLUDE_BOARD_HPP_

#include "teleporters.hpp"

#include <string>

class Board {
    int board_size_;

    // Each of the string's elements corresponds to a square on the board
    // ' ' = Normal tile
    // 'L' = Ladder
    // 'S' = Snake
    std::string board_;
    // List of Teleporters (Snakes/Ladders)
    Teleporters teleporters_;
public:
    Board() : board_size_(0), board_("") {}
    Board(int&);

    void AddTeleporter(TeleporterPair, char&);

    int GetNextPosition(int);

    // A game is complete when the player's position is >= the board's size
    bool IsGameComplete(int &position) {
	return position >= board_size_ - 1;
    }
};

#endif // INCLUDE_BOARD_HPP_
