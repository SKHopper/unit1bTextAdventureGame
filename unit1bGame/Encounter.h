#pragma once

#include "Lifeform.h"

//attack type and strength
struct Attack {
	bool isHeavy = false;
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
		stats(overrideStats), 
		Lifeform(
			(newSpawn) ? constants::ENCOUNTER_TYPE_STATS.at(type).maxHealth : overrideStats.maxHealth, 
			(newSpawn) ? constants::ENCOUNTER_TYPE_STATS.at(type).maxHealth : overrideStats.maxHealth
		)
	{
		if (newSpawn) {
			stats = constants::ENCOUNTER_TYPE_STATS.at(type);
		}
	};
	Attack attackPlayer();
	void exposite();
};