#ifndef INCLUDE_BOARD_HPP_
#define INCLUDE_BOARD_HPP_

#include "teleporters.hpp"

#include <string>

class Board {
    int board_size_;
    std::string board_;
    
    Teleporters teleporters_;
public:
    Board() : board_size_(0), board_("") {}
    Board(int&);

    void AddTeleporter(TeleporterPair, char&);

    int GetNextPosition(int);

    bool IsGameComplete(int &position) {
	return position >= board_size_ - 1;
    }
};

#endif // INCLUDE_BOARD_HPP_
