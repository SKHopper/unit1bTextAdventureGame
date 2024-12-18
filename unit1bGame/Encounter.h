#pragma once

#include "Lifeform.h"

struct attack {
	bool isHeavy;
	double dmg;
};

class Encounter : public Lifeform {
	encounterStats stats = {};
public:
	Encounter(
		constants::ENCOUNTER_TYPE type, 
		bool newSpawn, 
		encounterStats overrideStats = {}
	) : 
		stats((newSpawn) ? constants::ENCOUNTER_TYPE_STATS.at(type) : overrideStats), 
		Lifeform(
			(newSpawn) ? constants::ENCOUNTER_TYPE_STATS.at(type).maxHealth : overrideStats.maxHealth, 
			(newSpawn) ? constants::ENCOUNTER_TYPE_STATS.at(type).maxHealth : overrideStats.maxHealth
		)
	{};
	attack attackPlayer();
};