#include "game.hpp"

#include <iostream>
#include <fstream>

// Lazy but works. Ifstream of the input file
std::ifstream input("input.txt", std::fstream::in);

void Game::CreateBoard() {
    // Read in the board's size
    int board_size; input >> board_size;
    // Construct a new board object from the inputted size
    playing_board_ = Board(board_size);
}

void Game::ReadInTeleporters() {
    
    int num_of_teleporters, start, end;
    char teleporter_type;

    // Get the # of teleporters to input
    input >> num_of_teleporters;
    
    while (num_of_teleporters) {
	// Read in the teleporter's info
	input >> start >> teleporter_type >> end;

	// Create a new TeleporterPair
	TeleporterPair teleporter_coordinates = MakeTeleporterPair(start, end);

	// Add the teleporter to the board's list of teleporters
	playing_board_.AddTeleporter(teleporter_coordinates, teleporter_type);

	// Decrement the number of teleporters that need to be inputted
	--num_of_teleporters;
    }
}

void Game::ProcessDiceRollSequences() {
    int num_of_sequences, num_of_rolls, roll;

    // Read in the number of die sequences to read in
    input >> num_of_sequences;
    
    // Read in all dice sequences
    while (num_of_sequences) {

	// Read in the number of dice rolls
	input >> num_of_rolls;
	
	// Create a new sequence of dice rolls
	DiceRollSequence rolls(num_of_rolls);

	// Read in the die roll values
	for (int i = 0; i < num_of_rolls; ++i) {
	    input >> rolls[i];
	}

	// Player's position starts at -1, AKA 0 on a normal board
	// This is before they have rolled, and cannot get back to that position
	int position = -1;

	// Get the start/end iterator positions to iterate through the sequence
	auto rolls_iterator = rolls.begin();
	auto rolls_end = rolls.end();

	// Apply dice rolls while the end of the sequence hasn't been reached
	// AND while the player hasn't won
	while (rolls_iterator != rolls_end && !playing_board_.IsGameComplete(position)){
	    // Add the value of the die roll to the player's position
	    position += *rolls_iterator;
	    
	    // Check that the square landed on is a teleporter.
	    // If it is not, the same position inputted is returned
	    // Otherwise the player's new position is returned
	    position = playing_board_.GetNextPosition(position);
	    
	    // Increment the rolls_iterator
	    ++rolls_iterator;
	}
	// Print the end result of the dice rolls
	PrintResult(position);

	// Decrement the number of dice roll sequences to process
	--num_of_sequences;
    }
}

void Game::PrintResult(int &position) {
    // Print the end result of the player's dice sequence
    std::cout << (playing_board_.IsGameComplete(position) ?
		  "Winner!" : "Did not make it!") << std::endl;
}

TeleporterPair Game::MakeTeleporterPair(int start, int end) {
    // Positions need to be decremented because the board is assumed
    // to start at index 1, when all underlying data structures start at 0
    return TeleporterPair(start - 1, end - 1);
}
