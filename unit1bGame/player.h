#pragma once

#include "Key.h"
#include "Lifeform.h"

class Player : public Lifeform {
	Key testKey = Key(constants::stone);
	Key testKey2 = Key(constants::steel);
	vector<Item> inventory = {testKey, testKey, testKey2};
public:
	Player(double maxHealth, double health) : Lifeform(maxHealth, health) {};
	//beware pass by ref
	vector<Item>& getInventory();
	//all previous vector data replaced
	void setInventory(vector<Item> newInventory);
	//add new item to the end() of inventory vector
	void appendInventory(Item newItem);
	//displays inventory
	void exposite();
	void die();
};