#pragma once

#include <iostream>
#include <map>
#include <random>

using std::map, std::vector, std::string, std::cout, std::cin, std::endl;

namespace constants {
	const enum DOOR_TYPE {
		nullType = -1,
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
};

struct bivarInt {
	int x;
	int y;
};

//true if 0<=random float<=1 greater than weight
bool randomWeightedBoolean(double weight);
bool equateBivariateIntegers(bivarInt a, bivarInt b);
bivarInt sumBivariateIntegers(bivarInt a, bivarInt b);
bivarInt getDirectionDisplacement(constants::DIRECTION direction);
void resetInput();