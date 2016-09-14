#include "board.hpp"
#include "types.hpp"

Board::Board(int &size) {
    board_size_ = size;
    
    board_.assign(size, ' ');
}

void Board::AddTeleporter(TeleporterPair teleporter_coordinates,
			  char &teleporter_type) {
    board_[teleporter_coordinates.first] = teleporter_type;
    teleporters_.AddTeleporter(teleporter_coordinates, teleporter_type);
}

int Board::GetNextPosition(int current_square) {
    // Do nothing if the current square is normal typed
    if (board_[current_square] == ' ') {
	return current_square;
    } else {
	// Get the type of teleporter that was landed on
	char teleporter_type = board_[current_square];
	// Get the new position of the player from Teleporters::GetNextPosition
	
	return teleporters_.GetNextPosition(teleporter_type, current_square);
    }
}
