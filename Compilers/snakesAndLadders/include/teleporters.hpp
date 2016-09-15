#ifndef INCLUDE_TELEPORTERS_HPP_
#define INCLUDE_TELEPORTERS_HPP_

#include "types.hpp"

class Teleporters {
    TeleporterMap snakes_;
    TeleporterMap ladders_;

public:
    Teleporters();

    void AddTeleporter(TeleporterPair, char&);
    int GetNextPosition(char&, int);
};

#endif // INCLUDE_TELEPORTERS_HPP_
