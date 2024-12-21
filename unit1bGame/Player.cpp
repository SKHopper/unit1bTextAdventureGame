#include "Player.h"

vector<Item>& Player::getInventory(){
    return inventory;
}

void Player::setInventory(vector<Item> newInventory){
    inventory = newInventory;
}

void Player::appendInventory(Item newItem) {
    inventory.push_back(newItem);
}

void Player::exposite() {
    vector<string> displayNames;    //one of each
    vector<int> itemCounts;         //count per name

    int itemCount = inventory.size();
    if (itemCount) {//unempty inventory
        cout << "In my satchel there is ";
        for (Item& thisItem : inventory) {
            string displayName = thisItem.getDisplayName();
            int index = linearStringSearch(displayNames, displayName);
            if (index == -1) {//new name
                displayNames.push_back(displayName);
                itemCounts.push_back(1);
            }
            else {//prelisted name
                itemCounts.at(index)++;
            }
        }
        for (int i = 0; i < displayNames.size(); i++) {
            cout << itemCounts.at(i) << " " << displayNames.at(i);
            if (itemCounts.at(i) > 1) {//plurality
                cout << "s";
            }
            if (i < displayNames.size() - 1) {//comma listing
                cout << ", ";
            }
        }
    }
    else {//empty inventory
        cout << "There is nothing in my satchel";
    }
}

void Player::die() {
    setHealth(BASE_PLAYER_MAX_HEALTH / 2);
}

