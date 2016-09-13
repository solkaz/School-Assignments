#ifndef INCLUDE_TELEPORTERS_HPP_
#define INCLUDE_TELEPORTERS_HPP_

#include <map>

using TeleporterList = std::map<unsigned int, unsigned int>;

class Teleporters {
    TeleporterList snakes_;
    TeleporterList ladders_;
public:
    Teleporters();

    void AddTeleporter(char &teleporter_type,
		       unsigned int &start,
		       unsigned int &end);

    unsigned int GetNextPosition(char &teleporter_type,
				 unsigned int &current_pos) {
	if (teleporter_type == 'L') {
	    return ladders_[position];
	} else {
	    return snakes_[position];
	}	
    }
};

#endif // INCLUDE_TELEPORTERS_HPP_
