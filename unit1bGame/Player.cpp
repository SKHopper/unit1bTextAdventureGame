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
    if (itemCount) {
        cout << "In your satchel there is ";
        for (int i = 0; i < itemCount; i++) {
            cout << inventory.at(i).getDisplayName();
            if (i != itemCount - 1) {
                cout << ", ";
            }
        }
    }
    else {
        cout << "There is nothing in your satchel";
    }
}
