#include "Dungeon.h"

Dungeon::Dungeon(){
	//TODO MAYBE: in dungeon generation customization 
}

bivarInt Dungeon::getPlayerCoordinate() {
    return playerCoordinate;
}

vector<roomMapPoint> Dungeon::getRoomMap(){
    return roomMap;
}

void Dungeon::makeRoom(DungeonRoomSave knownRoomData, bivarInt coordinate) {
    DungeonRoom newRoom;
    DungeonRoom& RnewRoom = newRoom;
    RnewRoom.Generate(knownRoomData);
    roomMap.push_back({ RnewRoom, coordinate });
}

//make new save with only wooden doors
void Dungeon::makeStartRoom(){
    DungeonRoomSave startSave;
    for (int i = 0; i < 4; i++) {
        DoorWall tempSide = DoorWall();
        tempSide.generate(true, constants::wood);
        startSave.sides.push_back(tempSide);
    }
    makeRoom(startSave, { 0, 0 });
}

int Dungeon::getRoomIndex(bivarInt coordinate) {  //TODO: the code im about to write will be O(n) so yk 
    int i = 0;
    while (i < roomMap.size()) {
        if (equateBivariateIntegers(roomMap.at(i).coordinate, coordinate)) {
            return i;
        }
        i++;
    }
    return -1;
}

DungeonRoom& Dungeon::getRoom(bivarInt coordinate) {
    return roomMap.at(getRoomIndex(coordinate)).room;
}

vector<DoorWall> Dungeon::getAdjacentSides(bivarInt coordinate){ //TODO MAYBE: change to pass by ref "fill with" over "get"
    vector<DoorWall> sides;
    DoorWall tempSide;
    for (int i = 0; i < 4; i++) {
        constants::DIRECTION direction = static_cast<constants::DIRECTION>(i);
        sides.push_back(tempSide);
        bivarInt adjacentCoordinate = sumBivariateIntegers(coordinate, getDirectionDisplacement(direction));
        if (getRoomIndex(adjacentCoordinate) != -1) {
            DoorWall& Rside = sides.at(i);
            DoorWall& RtwinSide = getRoom(adjacentCoordinate).getSide(constants::DIRECTION_OPPOSITE.at(direction)); 
            Rside.generate(RtwinSide.getWallHasDoor(), RtwinSide.getType());
            Rside.setIsUnlocked(RtwinSide.getIsUnlocked());
        }
    }
    return sides;
}

void Dungeon::traverse(constants::DIRECTION direction) {
    cout << "Headed " << constants::DIRECTION_DISPLAY_NAME.at(direction) << ", ";
    getRoom(playerCoordinate).getSide(direction).setIsUnlocked(true);
    playerCoordinate = sumBivariateIntegers(playerCoordinate, getDirectionDisplacement(direction));
    if (getRoomIndex(playerCoordinate) == -1) {//if no room exists
        makeRoom({ getAdjacentSides(playerCoordinate) }, playerCoordinate);
        cout << "you haven't been in this chamber before.\n";
    }
    else {//unlock corresponding other side of door
        getRoom(playerCoordinate).getSide(constants::DIRECTION_OPPOSITE.at(direction)).setIsUnlocked(true);
        cout << "you've been in this chamber before.\n";
    }
}
