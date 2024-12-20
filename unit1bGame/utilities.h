#pragma once

#include <iostream>
#include <map>
#include <random>
#include <cctype>
#include <string>
//#include <sqlite3.h>

using std::map, std::vector, std::string, std::cout, std::cin, std::endl;

/*
* DOWNWARD CASTING - only allows polymorphic instance data but does allow nonpolymorphic functionality
* 
* //implicit cast up
* Base& Rbase = *new Derived();
* 
* //explicit cast down
* Derived& Rderived = *static_cast<Derived*>(&Rbase);
*/

//{x, y}
struct bivarInt {
	int x;
	int y;
};

struct encounterStats {
	int level;

	double maxHealth; 
	double lightAttackDmg; 
	double heavyAttackDmg;
	double heavyAttackChance;

	string encounterDisplayName; 
	string lightAttackDisplayMsg; 
	string heavyAttackDisplayMsg;
	string description;
};

namespace constants {
	//for both doors and associated keys, -1
	const enum DOOR_TYPE {
		nullDoorType = -1,
		wood = 0,
		stone = 1,
		steel = 2,
		special = 3
	};

	const vector<bivarInt> DOOR_TYPE_ODDS = {
		{wood, 15},
		{stone, 6},
		{steel, 3},
		{special, 1}
	};

	const vector<bivarInt> KEY_TYPE_ODDS = {
		{stone, 6},
		{steel, 3},
		{special, 1}
	};

	//for both doors and associated keys, excludes null type
	const map<DOOR_TYPE, string> DOOR_TYPE_DISPLAY_NAME = {
		{wood, "Wooden"},
		{stone, "Enchanted Stone"},
		{steel, "Ancient Engraved Steel"},
		{special, "[placeholder name special]"}
	};

	/*
	* cardinal
	* 
	*****north+
	**west-  east+
	****south-
	*/
	const enum DIRECTION {
		north = 0,
		east = 1,
		south = 2,
		west = 3
	};

	//lowercase plaintext
	const map<DIRECTION, string> DIRECTION_DISPLAY_NAME = {
		{north, "north"},
		{east, "east"},
		{south, "south"},
		{west, "west"}
	};
	
	const map<DIRECTION, DIRECTION> DIRECTION_OPPOSITE = {
		{north, south},
		{east, west},
		{south, north},
		{west, east}
	};

	//for discerning whether downward casting is possible, -1 for null type
	const enum ITEM_TYPE {
		nullItemType = -1,
		key = 0,
		placeholder1 = 1,
		placeholder2 = 2,
	};

	const vector<bivarInt> ITEM_TYPE_ODDS = {
		{key, 6},
		{placeholder1, 0},
		{placeholder2, 0}
	};

	const vector<string> SPECIAL_VOWELS = {"e", "u", "i", "y"};
	const vector<string> SPECIAL_CONSONANTS = { "r", "n", "t", "c" };

	const map<string, int> CONTROLS = {
		{"w", 0},
		{"a", 1},
		{"s", 2},
		{"d", 3},
		{"1", 4},
		{"2", 5},
		{"3", 6},
		{"4", 7}
	};

	const map<int, string> CONTROLS_DISPLAY = {
		{0, "w"},
		{1, "d"},
		{2, "s"},
		{3, "a"},
		{4, "1"},
		{5, "2"},
		{6, "3"},
		{7, "4"}
	};

	const enum ENCOUNTER_TYPE {
		nullEncounterType = -1,
		basicEncounter = 0
	};

	const vector<bivarInt> ENCOUNTER_TYPE_ODDS = {
		{basicEncounter, 1}
	}; 
	
	const vector<bivarInt> ENCOUNTER_LEVEL_ODDS = {
		{1, 10},
		{2, 7},
		{3, 3},
		{4, 2},
		{5, 1}
	};

	const map<ENCOUNTER_TYPE, encounterStats> ENCOUNTER_TYPE_STATS = {
		{basicEncounter, {
			1,
			3, 1, 4, (1/4),
			"Rotted Golem", "swings at you with a twitching claw", "throws its crippled form at you",
			"placeholder-description"

		}}
	};
};

struct encounterSpawnData {
	bool hasEncounter;
	bool previousEncounter;
	encounterStats previousStats;
	constants::ENCOUNTER_TYPE encounterType;
};

//true if a.x == b.x && a.y = b.y
bool equateBivariateIntegers(bivarInt a, bivarInt b);
//displacement addition
bivarInt sumBivariateIntegers(bivarInt a, bivarInt b);
//"x, y"
void displayBivariateIntegers(bivarInt integers);
//gets the unit integer vector of cardinal directions
bivarInt getDirectionDisplacement(constants::DIRECTION direction);
//for returning random enumerated type key from table based on relative odds
int selectFromOddsTable(vector<bivarInt> table);

void resetInput();
void clearTerminal();

//true if (0<=random float<=1) greater than weight
bool randomWeightedBoolean(double weight);
int randomInteger(int max);
string specialNameGenerator(int length);

int linearStringSearch(vector<string> arr, string a);