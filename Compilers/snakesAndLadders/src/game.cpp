#include "game.hpp"

#include <iostream>
#include <fstream>

std::ifstream input("input.txt", std::fstream::in);

void Game::CreateBoard() {
    int board_size; input >> board_size;
    playing_board_ = Board(board_size);
}

void Game::ReadInTeleporters() {
    
    int num_of_teleporters, start, end;
    char teleporter_type;
    
    input >> num_of_teleporters;
    while (num_of_teleporters) {
	input >> start >> teleporter_type >> end;

	// Create a new TeleporterPair
	TeleporterPair teleporter_coordinates = MakeTeleporterPair(start, end);

	// Add the teleporter
	playing_board_.AddTeleporter(teleporter_coordinates, teleporter_type);

	--num_of_teleporters;
    }
}

void Game::ProcessDiceRollSequences() {
    int num_of_sequences, num_of_rolls, roll;
    input >> num_of_sequences;
    while (num_of_sequences) {
	
	input >> num_of_rolls;
	// Create a new sequence of dice rolls
	DiceRollSequence rolls(num_of_rolls);

	// Read in the die roll values
	for (int i = 0; i < num_of_rolls; ++i) {
	    input >> rolls[i];
	}

	int position = -1;

	auto rolls_iterator = rolls.begin();
	auto rolls_end = rolls.end();
	
	while (rolls_iterator != rolls_end && !playing_board_.IsGameComplete(position)){
	    // Add the value of the die roll to the player's position and
	    // check that the square landed on is a teleporter.
	    // If it is not, the same position inputted is returned
	    position = position + *rolls_iterator;
	    std::cout << "position before: " << position << ' ';
	    position = playing_board_.GetNextPosition(position);
	    std::cout << "position after: " << position << std::endl;;
	    
	    // Increment the rolls_iterator
	    ++rolls_iterator;
	}
	std::cout << "position final: " << position << std::endl;
	// Print the end result of the dice rolls
	PrintResult(position);

	// Decrement the number of dice roll sequences to process
	--num_of_sequences;
    }
}

void Game::PrintResult(int &position) {
    std::cout << (playing_board_.IsGameComplete(position) ?
		  "Winner!" : "Did not make it!") << std::endl;
}

TeleporterPair Game::MakeTeleporterPair(int start, int end) {
    // Positions need to be decremented because the board is assumed
    // to start at index 1, when all underlying data structures start at 0
    return TeleporterPair(start - 1, end - 1);
}
