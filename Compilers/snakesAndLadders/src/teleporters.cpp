#include "teleporters.hpp"

#include <iostream>


Teleporters::Teleporters() {
    snakes_ = TeleporterMap();
    ladders_ = TeleporterMap();
}

void Teleporters::AddTeleporter(TeleporterPair new_teleporter, char &teleporter_type) {
    // Determine which Map needs to be added to
    if (teleporter_type == 'L') {
	ladders_.insert(new_teleporter);
    } else {
	snakes_.insert(new_teleporter);
    }
}

int Teleporters::GetNextPosition(char &teleporter_type, int start) {
    // Get the TeleporterMap to read from
    if (teleporter_type == 'L') {
	return ladders_[start];
    } else {
	return snakes_[start];
    }
}
