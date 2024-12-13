#pragma once

#include "utilities.h"

class DoorWall {
	bool isGenerated = false;
	bool wallHasDoor = false;
	constants::DOOR_TYPE type = constants::nullType;
	bool isUnlocked = false;
public:
	bool getIsGenerated();
	bool getWallHasDoor();
	constants::DOOR_TYPE getType();
	bool getIsUnlocked();

	void setIsGenerated(bool newValue);
	void setWallHasDoor(bool newValue);
	void setType(constants::DOOR_TYPE newValue);
	void setIsUnlocked(bool newValue);
	
	bool tryUnlock(constants::DOOR_TYPE keyType);

	void generate(bool newHasDoor, constants::DOOR_TYPE newType);
};