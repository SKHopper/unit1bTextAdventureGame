#pragma once

#include "Item.h"

class Key: public Item {
	constants::DOOR_TYPE keyType;
public:
	Key(constants::DOOR_TYPE newKeyType) : keyType(newKeyType), Item(constants::key, constants::DOOR_TYPE_DISPLAY_NAME.at(newKeyType) + " Unlock Rune") {};
	constants::DOOR_TYPE getKeyType();
};