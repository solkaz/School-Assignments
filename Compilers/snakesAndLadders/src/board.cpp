#include "board.hpp"

#include <algorithm>

Board::Board(int &size) {
    board_size_ = size;
    std::fill(board_.begin(), board_.end(), ' ');
}
