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

namespace constants {
	const enum DOOR_TYPE {
		nullDoorType = -1,
		wood = 0,
		stone = 1,
		steel = 2,
		special = 3
	};

	const map<DOOR_TYPE, string> DOOR_TYPE_DISPLAY_NAME = {
		{wood, "Wooden"},
		{stone, "Chisled Stone"},
		{steel, "Ancient Ornate Steel"},
		{special, "[placeholder name special]"}
	};

	/*
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

	const map<DIRECTION, string> DIRECTION_DISPLAY_NAME = {
		{north, "North"},
		{east, "East "},
		{south, "South"},
		{west, "West "}
	};
	
	const map<DIRECTION, DIRECTION> DIRECTION_OPPOSITE = {
		{north, south},
		{east, west},
		{south, north},
		{west, east}
	};

	const enum ITEM_TYPE {
		nullItemType = -1,
		key = 0,
		placeholder1 = 1,
		placeholder2 = 2,
	};
};

struct bivarInt {
	int x;
	int y;
};

//true if 0<=random float<=1 greater than weight
bool randomWeightedBoolean(double weight);
bool equateBivariateIntegers(bivarInt a, bivarInt b);
bivarInt sumBivariateIntegers(bivarInt a, bivarInt b);
void displayBivariateIntegers(bivarInt integers);
bivarInt getDirectionDisplacement(constants::DIRECTION direction);
void resetInput();
void clearTerminal();