#ifndef INCLUDE_BOARD_HPP_
#define INCLUDE_BOARD_HPP_

class Board {
    unsigned int board_size_;
    std::string board_;
    Teleporters teleporters_;
public:
    Board(unsigned_int&);
};

#endif // INCLUDE_BOARD_HPP_
