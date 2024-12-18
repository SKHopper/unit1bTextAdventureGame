#pragma once

#include <iostream>

#include "utilities.h"
#include "DoorWall.h"

//all generated data about a room to be saved 
struct DungeonRoomSave {
	std::vector<DoorWall> sides;
	bool hasEncounter;
	constants::ENCOUNTER_TYPE type;
	int encounterLevel;
};

class DungeonRoom {
	DungeonRoomSave roomSave;
public:
	DungeonRoom();
	//beware pass by ref
	DoorWall& getSide(constants::DIRECTION direction);
	//will fill room data not specified by room save
	void Generate(DungeonRoomSave save);
	//displays state of each side
	void exposit();
};