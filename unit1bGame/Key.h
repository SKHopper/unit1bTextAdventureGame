#pragma once

#include "Item.h"

class Key: public Item {
public:
	Key(constants::DOOR_TYPE newKeyType) : Item(constants::key, constants::DOOR_TYPE_DISPLAY_NAME.at(newKeyType) + " Unseal Rune") {
		getInstanceData().push_back(newKeyType);
	};
	constants::DOOR_TYPE getKeyType();
};