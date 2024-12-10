#pragma once

#include <iostream>

#include "Dungeon.h"

class DungeonRoom {
	DungeonSave roomSave;
public:
	DungeonRoom();
	void Generate(DungeonSave save);
	void exposit();
};