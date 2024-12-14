#pragma once

#include <iostream>

#include "utilities.h"
#include "DoorWall.h"

struct DungeonRoomSave {
	std::vector<DoorWall> sides;
	//more content
};

class DungeonRoom {
	DungeonRoomSave roomSave;
public:
	DungeonRoom();
	DoorWall& getSide(constants::DIRECTION direction);
	void Generate(DungeonRoomSave save);
	void exposit();
};