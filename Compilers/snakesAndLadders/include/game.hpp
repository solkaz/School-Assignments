#ifndef INCLUDE_GAME_HPP_
#define INCLUDE_GAME_HPP_

#include "board.hpp"
#include "types.hpp"

class Game {
    Board playing_board_;
    
public:
    void CreateBoard();

    void ReadInTeleporters();

    void ProcessDiceRollSequences();
    void PrintResult(int&);
    
    TeleporterPair MakeTeleporterPair(int, int);
};

#endif // INCLUDE_GAME_HPP_
