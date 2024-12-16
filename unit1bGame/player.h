#pragma once

#include "Key.h"

class Player {
	Key testKey = Key(constants::stone);
	vector<Item> inventory = {testKey};
public:
	//beware pass by ref
	vector<Item>& getInventory();
	//all previous vector data replaced
	void setInventory(vector<Item> newInventory);
	//add new item to the end() of inventory vector
	void appendInventory(Item newItem);
	//displays inventory
	void exposite();
};