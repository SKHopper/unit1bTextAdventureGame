#include "DoorWall.h"

bool DoorWall::getIsGenerated(){
    return isGenerated;
}

bool DoorWall::getWallHasDoor(){
    return wallHasDoor;
}

constants::DOOR_TYPE DoorWall::getType(){
    return type;
}

bool DoorWall::getIsUnlocked(){
    return isUnlocked;
}

void DoorWall::setIsGenerated(bool newValue) {
    isGenerated = newValue;
}

void DoorWall::setWallHasDoor(bool newValue) {
    wallHasDoor = newValue;
}

void DoorWall::setType(constants::DOOR_TYPE newValue) {
    type = newValue;
}

void DoorWall::setIsUnlocked(bool newValue) {
    isUnlocked = newValue;
}

bool DoorWall::tryUnlock(constants::DOOR_TYPE keyType) {
    if (keyType == type) {
        isUnlocked = true;
        return true;
    }
    else {
        return false;
    }
}

void DoorWall::generate(bool newHasDoor, constants::DOOR_TYPE newType){
    if (not isGenerated) {
        isGenerated = true;
        wallHasDoor = newHasDoor;

        if (wallHasDoor) {
            type = newType;
            isUnlocked = type == constants::wood;
        }
    }
}
