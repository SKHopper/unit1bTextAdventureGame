#include <iostream>

#include "Dungeon.h"
#include "player.h"

void displayRoomOptions(Player playerCharacter) {
    cout << "Entre door: ";
    for (int i = 0; i < 4; i++) {
        cout
            << "["
            << i + 1
            << "]"
            << constants::DIRECTION_DISPLAY_NAME.at(static_cast<constants::DIRECTION>(i));
        if (i != 3) {
            cout << ", ";
        }
    }
    cout << endl;
    cout << endl;
}

int getPlayerInput(int highestPlayerChoice) {
    highestPlayerChoice++;
    cout << "Your choice: ";
    int playerInput;
    cin >> playerInput;
    if (cin.fail() || playerInput > highestPlayerChoice) {
        resetInput();
        playerInput = getPlayerInput(highestPlayerChoice);
    }
    return playerInput - 1;
}

void playerTryEntreDoor(Dungeon& playerDungeon, Player& playerCharacter, int playerChoice) {
    clearTerminal();
    constants::DIRECTION direction = static_cast<constants::DIRECTION>(playerChoice);
    DoorWall& side = playerDungeon.getRoom(playerDungeon.getPlayerCoordinate()).getSide(direction);
    vector<Item>& inventory = playerCharacter.getInventory();
    bool entreSuccess = side.getIsUnlocked();
    if (side.getWallHasDoor() && !entreSuccess) {//if wall is not just locked because no door
        for (int i = 0; i < inventory.size(); i++) {
            Item& keyProspect = inventory.at(i);
            if (keyProspect.getType() == constants::key) {
                entreSuccess = side.tryUnlock((*static_cast<Key*>(&keyProspect)).getKeyType());
                if (entreSuccess) {
                    cout << "You used one " + keyProspect.getDisplayName() << ", \n";
                    inventory.erase(inventory.begin() + i);
                    break;
                }
            }
        }
    }
    if (entreSuccess) {
        playerDungeon.traverse(direction);
    }
    else {
        if (side.getWallHasDoor()) {
            cout 
                << "Your satchel does not contain the rune to open the " 
                << constants::DIRECTION_DISPLAY_NAME.at(direction)
                << " door";
        }
        else {
            cout 
                << "The wall to the "
                << constants::DIRECTION_DISPLAY_NAME.at(direction)
                << " is impassable";
        }
        cout 
            << ", the path is blocked."
            << endl;
    }
}

void playerAct(Dungeon& playerDungeon, Player& playerCharacter) {
    DungeonRoom& playerRoom = playerDungeon.getRoom(playerDungeon.getPlayerCoordinate());
    int playerChoice = getPlayerInput(3);
    if (playerChoice <= 3) {
        playerTryEntreDoor(playerDungeon, playerCharacter, playerChoice);
    }
}

//call room and player to display refreshed info
void exposite(Dungeon playerDungeon, Player playerCharacter) {
    DungeonRoom playerRoom = playerDungeon.getRoom(playerDungeon.getPlayerCoordinate());
    playerRoom.exposit();
    cout << endl;
    playerCharacter.exposite();
    cout << endl;
    cout << endl;
}

void play() {
    Player playerCharacter;
    Dungeon playerDungeon;
    playerDungeon.makeStartRoom();
    while (true) {
        exposite(playerDungeon, playerCharacter);
        displayRoomOptions(playerCharacter);
        playerAct(playerDungeon, playerCharacter);
    }
}

int main() {
    //new seed per execute
    srand(time(0));
    play();
}