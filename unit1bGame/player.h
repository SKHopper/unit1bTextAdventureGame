#pragma once

#include "Key.h"

class Player {
	vector<Item> inventory;
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