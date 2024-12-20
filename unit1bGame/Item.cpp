#include "Item.h"

//Item::Item(constants::ITEM_TYPE newType, string newDisplayName) : 

vector<double>& Item::getInstanceData() {
    return instanceData;
}

constants::ITEM_TYPE Item::getType() {
    return type;
}

void Item::setType(constants::ITEM_TYPE newType) {
    type = newType;
}

string Item::getDisplayName() {
    return displayName;
}

void Item::setDisplayName(string newDisplayName){
    displayName = newDisplayName;
}
