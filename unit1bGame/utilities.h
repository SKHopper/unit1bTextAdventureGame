#pragma once

#include <iostream>
#include <map>
#include <random>
#include <cctype>
#include <string>
#include <chrono>

#define WALL_HAS_DOOR_CHANCE 0.85

#define BASE_ESCAPE_CHANCE 0.08

#define BASE_DODGE_CHANCE 0.5
#define DODGED_ATTACK_DAMAGE 0.0

#define BASE_LIGHT_BLOCK_CHANCE 0.2
#define BASE_HEAVY_BLOCK_CHANCE 0.8
#define BASE_BLOCK_DAMAGE_MULTIPLIER 0.1

#define BASE_PLAYER_LIGHT_ATTACK_DMG -2.0
#define BASE_PLAYER_HEAVY_ATTACK_DMG -4.0

#define PLAYER_ALLOWED_INPUT_SECS 3.0

#define BASE_PLAYER_MAX_HEALTH 20.0

using
	std::map,
	std::vector,
	std::string,
	std::cout,
	std::cin,
	std::endl;
using namespace std::chrono;

//{x, y}
struct bivarInt {
	int x;
	int y;
};

//for encounter instances to hold and for saving between respawns
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

	//for loot table
	const vector<bivarInt> DOOR_TYPE_ODDS = {
		{wood, 15},
		{stone, 6},
		{steel, 3},
		{special, 1}
	};

	//for loot table
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
	
	//cardinal opposite
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

	//for loot table
	const vector<bivarInt> ITEM_TYPE_ODDS = {
		{key, 6},
		{placeholder1, 0},
		{placeholder2, 0}
	};

	//for procedural names
	const vector<string> SPECIAL_VOWELS = {"e", "u", "i", "y"};
	//for procedural names
	const vector<string> SPECIAL_CONSONANTS = { "r", "n", "t", "c" };

	//player in to program switch pattern
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

	//program switch pattern to display names
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

	//used to select stats on new spawn
	const enum ENCOUNTER_TYPE {
		nullEncounterType = -1,
		basicEncounter = 0
	};

	//for loot table
	const vector<bivarInt> ENCOUNTER_TYPE_ODDS = {
		{basicEncounter, 1}
	}; 

	//for loot table
	const vector<bivarInt> ENCOUNTER_LEVEL_ODDS = {
		{1, 6},
		{2, 4},
		{3, 2}
	};

	const map<int, string> ENCOUNTER_LEVEL_DISPLAY_NAME = {
		{1, "Meak"},
		{2, "Menacing"},
		{3, "Berserk"}
	};

	//for encounter instance construction on new spawn
	const map<ENCOUNTER_TYPE, encounterStats> ENCOUNTER_TYPE_STATS = {
		{
			basicEncounter, 
			{
				1,
				3, -1, -4, 0.25,
				"Rotted Golem", "swings at me with a twitching claw.", "throws its crippled form at me.", "placeholder-description"
			}
		}
	};
};

//attack type and strength
const struct Attack {
	bool isHeavy;
	double dmg;
};

//data for dungeon rooms to handle encountering on traverse in
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
//maybe better than random std::rand()
int randomInteger(int max);
string specialNameGenerator(int length);

//-1 if fail
int linearStringSearch(vector<string> arr, string a);

//multiplier for effects (e.g. chances and dmgs) based on player input delay proximity to perfect and failure
double getElapsedSecondsResultMultiplier(double elapsedSeconds);