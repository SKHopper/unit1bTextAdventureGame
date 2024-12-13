#include <random>

#include "DungeonRoom.h"

DungeonRoom::DungeonRoom() {

}

void DungeonRoom::Generate(DungeonRoomSave save){
	for (DoorWall& Rside : save.sides) {
		if (not Rside.getIsGenerated()) {
			Rside.generate(randomWeightedBoolean(0.8), constants::wood);
		}
	}
	roomSave = save;
}

void DungeonRoom::exposit(){
	for (int i = 0; i < 4; i++) {
		DoorWall tempSide = roomSave.sides.at(i);
		string sideDisplayName;
		if (tempSide.getWallHasDoor()) {
			sideDisplayName = (tempSide.getIsUnlocked()) ? "an unlocked" : "a locked";
			sideDisplayName += " ";
			sideDisplayName += constants::DOOR_TYPE_DISPLAY_NAME.at(tempSide.getType());
			sideDisplayName += " door";
		}
		else {
			sideDisplayName = "a wall";
		}
		cout 
			<< "On the "
			<< constants::DIRECTION_DISPLAY_NAME.at(i) 
			<< " side of the room there is "
			<< sideDisplayName
			<< endl;
	}
}
