#include "game.hpp"

int main() {

    // Create new instances of a Snakes And Ladders Game
    Game game_instance;

    // Create the Game's board
    game_instance.CreateBoard();
    
    // Read in the list of snakes and ladders
    game_instance.ReadInTeleporters();

    // Process the dice roll sequences
    game_instance.ProcessDiceRollSequences();

    // Exit the program
    return 0;
}
