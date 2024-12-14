#pragma once

#include "utilities.h"

class DoorWall {
	bool isGenerated = false;
	bool wallHasDoor = false;
	constants::DOOR_TYPE type = constants::nullType;
	bool isUnlocked = false;
public:
	void generate(bool newHasDoor, constants::DOOR_TYPE newType);
	bool getIsGenerated();
	void setIsGenerated(bool newValue);

	bool getWallHasDoor();
	void setWallHasDoor(bool newValue);

	constants::DOOR_TYPE getType();
	void setType(constants::DOOR_TYPE newValue);

	bool tryUnlock(constants::DOOR_TYPE keyType);
	bool getIsUnlocked();
	void setIsUnlocked(bool newValue);
};