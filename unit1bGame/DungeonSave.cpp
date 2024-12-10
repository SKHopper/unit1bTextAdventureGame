#include "DungeonSave.h"

vector<DoorWall>& DungeonSave::getSides() {
	vector<DoorWall>& Rsides = sides;
	return sides;
}

void DungeonSave::setSides(vector<DoorWall> newSides) {
	sides = newSides;
}
