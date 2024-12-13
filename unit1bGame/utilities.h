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

	const enum DIRECTION {
		north = 0,
		west = 1,
		south = 2,
		east = 3
	};

	const map<DOOR_TYPE, string> DOOR_TYPE_DISPLAY_NAME = {
		{wood, "Wooden"},
		{stone, "Chisled Stone"},
		{steel, "Ancient Ornate Steel"},
		{special, "[come up with a name for a special material for unique mechanics]"}
	};

	const map<int, string> DIRECTION_DISPLAY_NAME = {
		{0, "North"},
		{1, "West "},
		{2, "South"},
		{3, "East "}
	};
};

//true if 0<=random float<=1 greater than weight
bool randomWeightedBoolean(double weight);
