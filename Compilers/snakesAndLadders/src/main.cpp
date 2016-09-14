#include "game.hpp"

int main() {

    Game game_instance;

    game_instance.CreateBoard();
    
    // Read in the list of snakes and ladders
    game_instance.ReadInTeleporters();

    // Process the dice roll sequences
    game_instance.ProcessDiceRollSequences();
    
    return 0;
}
