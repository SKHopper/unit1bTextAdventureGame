#pragma once

#include "Key.h"

class Player {
	vector<Item> inventory;
public:
	vector<Item>& getInventory();
	void setInventory(vector<Item> newInventory);
	void appendInventory(Item newItem);
	void exposite();
};