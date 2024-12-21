#pragma once

#include <iostream>

#include "DoorWall.h"
#include "Item.h"

//all generated data about a room to be saved 
struct DungeonRoomSave {
	std::vector<DoorWall> sides;
	encounterSpawnData encounterData;
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
	encounterSpawnData getEncounter();
	Item killEncounter();
};