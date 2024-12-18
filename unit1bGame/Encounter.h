#pragma once

#include "Lifeform.h"

class Encounter : public Lifeform {
	encounterStats stats = {};
public:
	Encounter(double maxHealth, double health, constants::ENCOUNTER_TYPE type, bool newSpawn, encounterStats overrideStats) : stats((newSpawn) ? constants::ENCOUNTER_TYPE_STATS.at(type) : overrideStats), Lifeform(maxHealth, health) {};
	
};