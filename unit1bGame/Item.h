#pragma once

#include "utilities.h"

class Item {
	constants::ITEM_TYPE type;
	string displayName;
	//throw item type specific data in here
	vector<double> instanceData;
public:
	Item(constants::ITEM_TYPE newType = constants::nullItemType, string newDisplayName = "UNINITIALIZED ITEM") : type(newType), displayName(newDisplayName) {};
	//downward casting depends on this
	virtual ~Item() {};

	vector<double>& getInstanceData();

	constants::ITEM_TYPE getType();
	void setType(constants::ITEM_TYPE newType);

	string getDisplayName();
	void setDisplayName(string newDisplayName);
};