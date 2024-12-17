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
    int itemCount = inventory.size();
    vector<string> displayNames;
    vector<int> itemCounts;
    if (itemCount) {
        cout << "In your satchel there is ";
        for (Item& thisItem : inventory) {
            string displayName = thisItem.getDisplayName();
            int index = linearStringSearch(displayNames, displayName);
            if (index == -1) {
                displayNames.push_back(displayName);
                itemCounts.push_back(1);
            }
            else {
                itemCounts.at(index)++;
            }
        }
        for (int i = 0; i < displayNames.size(); i++) {
            cout << itemCounts.at(i) << " " << displayNames.at(i);
            if (itemCounts.at(i) > 1) {
                cout << "s";
            }
            if (i < displayNames.size() - 1) {
                cout << ", ";
            }
        }
    }
    else {
        cout << "There is nothing in your satchel";
    }
}
