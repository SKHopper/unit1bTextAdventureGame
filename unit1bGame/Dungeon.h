#pragma once

#include <iostream>
#include <vector>

#include "utilities.h"
#include "DungeonRoom.h"

struct roomMapPoint {
	DungeonRoom room;
	bivarInt coordinate;
};

class Dungeon {
	vector<roomMapPoint> roomMap;
	bivarInt playerCoordinate;
public:
	Dungeon();
	void makeRoom(DungeonRoomSave knownRoomData, bivarInt coordinate);
	void makeStartRoom();
	
	bivarInt getPlayerCoordinate();
	vector<roomMapPoint> getRoomMap();
	int getRoomIndex(bivarInt coordinate);
	DungeonRoom& getRoom(bivarInt coordinate);
	vector<DoorWall> getAdjacentSides(bivarInt coordinate);
	void traverse(constants::DIRECTION direction);
};