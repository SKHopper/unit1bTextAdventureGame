#include <random>

#include "DungeonRoom.h"

DungeonRoom::DungeonRoom() {

}

DoorWall& DungeonRoom::getSide(constants::DIRECTION direction){
	return roomSave.sides.at(direction);
}

void DungeonRoom::Generate(DungeonRoomSave save){
	for (DoorWall& Rside : save.sides) {
		if (not Rside.getIsGenerated()) {
			Rside.generate(randomWeightedBoolean(0.3), static_cast<constants::DOOR_TYPE>(selectFromOddsTable(constants::DOOR_TYPE_ODDS)));
		}
	}
	roomSave = save;
}

void DungeonRoom::exposit() {
	for (int i = 0; i < 4; i++) {
		constants::DIRECTION sideDirection = static_cast<constants::DIRECTION>(i);
		DoorWall tempSide = roomSave.sides.at(i);
		string sideDisplayName;
		if (tempSide.getWallHasDoor()) {
			sideDisplayName = (tempSide.getIsUnlocked()) ? "an Unsealed" : "a Sealed";
			sideDisplayName += " ";
			sideDisplayName += constants::DOOR_TYPE_DISPLAY_NAME.at(tempSide.getType());
			sideDisplayName += " Door";
		}
		else {
			sideDisplayName = "a Wall";
		}
		cout
			<< ((i) ? "to the " : "To the ")
			<< constants::DIRECTION_DISPLAY_NAME.at(sideDirection) 
			<< " there is "
			<< sideDisplayName
			<< ((i == 3) ? "." : ",\n");
	}
}
