#pragma once

#include <iostream>
#include <map>

using std::map, std::string;

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

	map<int, string> DOOR_TYPE_DISPLAY_NAME{
		{0, "Wooden"},
		{1, "Chisled Stone"},
		{2, "Ancient Ornate Steel"},
		{3, "[come up with a name for a special material for unique mechanics]"}
	};

	map<int, string> DIRECTION_DISPLAY_NAME{
		{0, "North"},
		{1, "West"},
		{2, "South"},
		{3, "East"}
	};
};

static bool randomWeightedBoolean(double weight);