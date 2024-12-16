#pragma once

#include <iostream>
#include <map>
#include <random>

using std::map, std::vector, std::string, std::cout, std::cin, std::endl;

/*
* DOWNWARD CASTING:
* 
* Derived derived(constants::wood);
* Base base = derived;
* Base* Pbase = &derived;
* Derived* Pderived = static_cast<Derived*>(Pbase);
* Derived retrievedDerived = *Pderived;
* 
* Derived derived = *static_cast<Key*>(&base)
*/

//{x, y}
struct bivarInt {
	int x;
	int y;
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

	const vector<bivarInt> DOOR_TYPE_ODDS = {
		{wood, 12},
		{stone, 6},
		{steel, 3},
		{special, 1}
	};

	const vector<bivarInt> KEY_TYPE_ODDS = {
		{stone, 6},
		{steel, 3},
		{special, 1}
	};

	const vector<bivarInt> ITEM_TYPE_ODDS = {
		{key, 6},
		{placeholder1, 0},
		{placeholder2, 0}
	};
};

//true if (0<=random float<=1) greater than weight
bool randomWeightedBoolean(double weight);
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
