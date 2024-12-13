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
	void Generate(DungeonRoomSave save);
	void exposit();
};