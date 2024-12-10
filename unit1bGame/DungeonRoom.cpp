#include <random>

#include "DungeonRoom.h"

DungeonRoom::DungeonRoom() {
}

void DungeonRoom::Generate(DungeonSave save){
	for (DoorWall& Rside : save.getSides()) {
		if (Rside = -1) {
			Rside = rand() % 2;
		}
	}
	roomSave = save;
}

void DungeonRoom::exposit(){
	for (int i = 0; i < 4; i++) {
		cout<<
	}
}
