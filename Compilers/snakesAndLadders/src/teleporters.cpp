#include "teleporters.hpp"

Teleporters::Teleporters() {
    // Construct new TeleporterMap objects for both
    // teleporter types
    snakes_ = TeleporterMap();
    ladders_ = TeleporterMap();
}

void Teleporters::AddTeleporter(TeleporterPair new_teleporter, char &teleporter_type) {
    // Determine which Map needs to be added to and add the teleporter
    if (teleporter_type == 'L') {
	ladders_.insert(new_teleporter);
    } else {
	snakes_.insert(new_teleporter);
    }
}

int Teleporters::GetNextPosition(char &teleporter_type, int start) {
    // Get the TeleporterMap to read from and get the player's new position
    if (teleporter_type == 'L') {
	return ladders_[start];
    } else {
	return snakes_[start];
    }
}
