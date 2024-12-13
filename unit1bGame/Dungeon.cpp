#include "Dungeon.h"

Dungeon::Dungeon(){
	//TODO MAYBE: in dungeon generation customization 
}

DungeonRoom Dungeon::makeStartRoom(){
    DungeonRoomSave roomSave;
    for (int i = 0; i < 4; i++) {
        DoorWall tempSide = DoorWall();
        tempSide.generate(true, constants::wood);
        roomSave.sides.push_back(tempSide); 
    }
    DungeonRoom newRoom; //dont try and by ref this unless you have too much free time      //trust me
    newRoom.Generate(roomSave);
	return newRoom; 
}
