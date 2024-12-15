#include <iostream>

#include "Dungeon.h"
#include "player.h"

void displayRoomMenu(Dungeon playerDungeon, Player playerCharacter) {
    DungeonRoom playerRoom = playerDungeon.getRoom(playerDungeon.getPlayerCoordinate());
    displayBivariateIntegers(playerDungeon.getPlayerCoordinate());//test
    playerRoom.exposit();
    cout << endl;
    playerCharacter.exposite();
    cout << endl;
    cout << endl;
    cout << "Entre door: ";
    for (int i = 0; i < 4; i++) {
        cout
            << constants::DIRECTION_DISPLAY_NAME.at(static_cast<constants::DIRECTION>(i))
            << "["
            << i + 1
            << "]";
        if (i != 3) {
            cout << ", ";
        }
    }
}

int getPlayerInput(int highestPlayerChoice) {
    cout << "Your choice:";
    int playerInput;
    cin >> playerInput;
    if (cin.fail() || playerInput > highestPlayerChoice) {
        resetInput();
        playerInput = getPlayerInput(highestPlayerChoice);
    }
    return playerInput;
}

void playerTryEntreDoor(Dungeon& playerDungeon, Player& playerCharacter, int playerChoice) {
    constants::DIRECTION direction = static_cast<constants::DIRECTION>(playerChoice);
    DoorWall& side = playerDungeon.getRoom(playerDungeon.getPlayerCoordinate()).getSide(direction);
    vector<Item>& inventory = playerCharacter.getInventory();
    bool entreSuccess = true;
    if (not side.getIsUnlocked()) {
        for (int i = 0; i < inventory.size(); i++) {//TODO: this shit is ass    
            Item& keyProspect = inventory.at(i);
            if (keyProspect.getType() == constants::key) {
                entreSuccess = side.tryUnlock((*static_cast<Key*>(&keyProspect)).getKeyType());
                if (entreSuccess) {
                    inventory.erase(inventory.begin() + i);
                    cout << "You used one " + keyProspect.getDisplayName() << endl;
                    break;
                }
            }
        }
    }
    if (entreSuccess) {
        playerDungeon.traverse(direction);
    }
}

void playerAct(Dungeon& playerDungeon, Player& playerCharacter) {
    DungeonRoom& playerRoom = playerDungeon.getRoom(playerDungeon.getPlayerCoordinate());
    int playerChoice = getPlayerInput(4);
    if (playerChoice < 4) {
        playerTryEntreDoor(playerDungeon, playerCharacter, playerChoice);
    }
}

void play() {
    Player playerCharacter;
    Dungeon playerDungeon;
    playerDungeon.makeStartRoom();
    while (true) {
        displayRoomMenu(playerDungeon, playerCharacter);
        cout << endl;
        playerAct(playerDungeon, playerCharacter);
    }
}

int main() {
    //new seed per execute
    srand(time(0));
    play();
}