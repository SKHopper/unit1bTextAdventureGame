#include "Dungeon.h"

Dungeon::Dungeon(){
	//TODO MAYBE: in dungeon generation customization 
}

bivarInt Dungeon::getPlayerCoordinate() {
    return playerCoordinate;
}

void Dungeon::setPlayerCoordinate(bivarInt newCoordinate) {
    playerCoordinate = newCoordinate;
}

vector<roomMapPoint> Dungeon::getRoomMap(){
    return roomMap;
}

void Dungeon::displayMap() {
    for (int i = mapExtents.at(0); i >= mapExtents.at(2); i--) {//top north to bottom south
        for (int j = mapExtents.at(1); j >= mapExtents.at(3); j--) {//left east to right west
            if (equateBivariateIntegers(getPlayerCoordinate(), { j, i })) {//where player is
                cout << "[+]";
            }
            else if (equateBivariateIntegers({ j, i }, { 0,0 })) {//where origin is
                cout << "[X]";
            }
            else if (getRoomIndex({ j, i }) != -1) {//explored room
                cout << "[ ]";
            }
            else {//unexplored room
                cout << " . ";
            }
        }
        cout << endl;
    }
}

DungeonRoom Dungeon::makeRoom(DungeonRoomSave knownRoomData, bivarInt coordinate) {
    DungeonRoom newRoom;
    newRoom.Generate(knownRoomData);
    roomMap.push_back({ newRoom, coordinate });

    if (coordinate.y > mapExtents.at(0)) {
        mapExtents.at(0) = coordinate.y;
    } 
    else if (coordinate.y < mapExtents.at(2)) {
        mapExtents.at(2) = coordinate.y;
    }
    if (coordinate.x > mapExtents.at(1)) {
        mapExtents.at(1) = coordinate.x;
    }
    else if (coordinate.x < mapExtents.at(3)) {
        mapExtents.at(3) = coordinate.x;
    }

    return newRoom;
}

//make new save with only wooden doors
void Dungeon::makeStartRoom(){
    DungeonRoomSave startSave;

    startSave.encounterData.hasEncounter = false;
    for (int i = 0; i < 4; i++) {
        DoorWall tempSide = DoorWall();
        tempSide.generate(true, constants::wood);
        startSave.sides.push_back(tempSide);
    }

    makeRoom(startSave, { 0, 0 });
}

int Dungeon::getRoomIndex(bivarInt coordinate) {  //TODO MAYBE: the code im about to write will be O(n) so yk 
    int i = 0;
    while (i < roomMap.size()) {
        if (equateBivariateIntegers(roomMap.at(i).coordinate, coordinate)) {
            return i;//index
        }
        i++;
    }
    return -1;//fail
}

DungeonRoom& Dungeon::getRoom(bivarInt coordinate) {
    return roomMap.at(getRoomIndex(coordinate)).room;
}

vector<DoorWall> Dungeon::getAdjacentSides(bivarInt coordinate){ //TODO MAYBE: change to pass by ref thus "fill with" over "get"
    vector<DoorWall> sides;
    DoorWall tempSide;

    for (int i = 0; i < 4; i++) {
        constants::DIRECTION direction = static_cast<constants::DIRECTION>(i);
        bivarInt adjacentCoordinate = sumBivariateIntegers(coordinate, getDirectionDisplacement(direction));

        sides.push_back(tempSide);    //TODO MAYBE: surely you can just copy object value then append without ref??

        if (getRoomIndex(adjacentCoordinate) != -1) { 
            DoorWall& RtwinSide = getRoom(adjacentCoordinate).getSide(constants::DIRECTION_OPPOSITE.at(direction)); 

            DoorWall& Rside = sides.at(i);
            Rside.generate(RtwinSide.getWallHasDoor(), RtwinSide.getType());
            Rside.setIsUnlocked(RtwinSide.getIsUnlocked());
        }
    }
    return sides;
}

encounterSpawnData Dungeon::traverse(constants::DIRECTION direction) {
    getRoom(playerCoordinate).getSide(direction).setIsUnlocked(true);
    cout << "Headed " << constants::DIRECTION_DISPLAY_NAME.at(direction) << ", ";
    playerCoordinate = sumBivariateIntegers(playerCoordinate, getDirectionDisplacement(direction));
    lastDirectionMoved = direction;

    DungeonRoom newRoom;
    DungeonRoom& RnewRoom = newRoom;

    if (getRoomIndex(playerCoordinate) == -1) {//if no room exists
        bool hasEncounter = randomWeightedBoolean( /*0.85*/ 0 );
        RnewRoom = makeRoom(
            {
                getAdjacentSides(playerCoordinate),
                {
                    hasEncounter,
                    false,
                    {},
                    (hasEncounter) ?
                        static_cast<constants::ENCOUNTER_TYPE>(selectFromOddsTable(constants::ENCOUNTER_TYPE_ODDS))
                    : constants::nullEncounterType
                }
            }, 
            playerCoordinate
        );
        cout << "you haven't been in this chamber before.\n";
    }
    else {//unlock corresponding other side of door
        RnewRoom = getRoom(playerCoordinate);
        RnewRoom.getSide(constants::DIRECTION_OPPOSITE.at(direction)).setIsUnlocked(true);
        cout << "you've been in this chamber before.\n";
    }
    return RnewRoom.getEncounter();
}

void Dungeon::escape() {
    traverse(constants::DIRECTION_OPPOSITE.at(lastDirectionMoved));
}

vector<int>& Dungeon::getMapExtents() {
    return mapExtents;
}
