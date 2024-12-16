#pragma once

#include "utilities.h"

class DoorWall {
	bool isGenerated = false;
	bool wallHasDoor = false;
	constants::DOOR_TYPE type = constants::nullDoorType;
	bool isUnlocked = false;
public:
	//confirms whether this side has a door of new type or just a wall
	void generate(bool newHasDoor, constants::DOOR_TYPE newType);
	bool getIsGenerated();
	void setIsGenerated(bool newValue);

	bool getWallHasDoor();
	void setWallHasDoor(bool newValue);

	constants::DOOR_TYPE getType();
	void setType(constants::DOOR_TYPE newValue);

	//equates type of key and door
	bool tryUnlock(constants::DOOR_TYPE keyType);
	bool getIsUnlocked();
	void setIsUnlocked(bool newValue);
};