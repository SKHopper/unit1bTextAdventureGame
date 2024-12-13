#pragma once

#include <iostream>
#include <vector>

#include "utilities.h"
#include "DungeonRoom.h"


class Dungeon {
public:
	Dungeon();
	DungeonRoom makeStartRoom();
};