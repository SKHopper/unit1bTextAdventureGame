#pragma once

#include <vector>

#include "doorWall.h"

using std::vector;

class DungeonSave {
	vector<DoorWall> sides;
	//contents
public:
	vector<DoorWall>& getSides();
	void setSides(vector<DoorWall> newSides);
};