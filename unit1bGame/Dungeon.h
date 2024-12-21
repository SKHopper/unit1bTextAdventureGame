#pragma once

#include <iostream>
#include <vector>

#include "DungeonRoom.h"

//a point on a hypothetical 2D array of rooms, holding object and specifying indices
struct roomMapPoint {
	DungeonRoom room;
	bivarInt coordinate;
};

class Dungeon {
	//all active room objects in this dungeon, unorganized
	vector<roomMapPoint> roomMap;
	//the indicies of the room the player is in on a hypothetical 2D array
	bivarInt playerCoordinate;
	constants::DIRECTION lastDirectionMoved;
	//furthest distances in cardinal directions with active rooms
	vector<int> mapExtents = {0, 0, 0, 0};
public:
	Dungeon();
	//appends ref of new room to roomMap
	DungeonRoom makeRoom(DungeonRoomSave knownRoomData, bivarInt coordinate);
	//appends ref of new (0, 0) fully unlocked room to roomMap
	void makeStartRoom();
	
	bivarInt getPlayerCoordinate();	
	void setPlayerCoordinate(bivarInt newCoordinate);
	vector<roomMapPoint> getRoomMap();
	void displayMap();
	int getRoomIndex(bivarInt coordinate);
	//beware pass by ref
	DungeonRoom& getRoom(bivarInt coordinate);
	//returns the sides of active rooms that would be the other sides of the sides of the room at specified coordinate
	vector<DoorWall> getAdjacentSides(bivarInt coordinate);
	//moves player coordinate by direction's unit vector and creates new room if necessary
	encounterSpawnData traverse(constants::DIRECTION direction);
	void escape();
	//beware pass by ref
	vector<int>& getMapExtents();
};