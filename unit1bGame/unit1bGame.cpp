#include <iostream>

#include "Dungeon.h"
#include "Player.h"
#include "Encounter.h"

void displayRoomOptions(Player playerCharacter) {
    cout << "Entre door: ";
    for (int i = 0; i < 4; i++) {
        cout
            << "["
            << constants::CONTROLS_DISPLAY.at(i)
            << "]"
            << constants::DIRECTION_DISPLAY_NAME.at(static_cast<constants::DIRECTION>(i));
        if (i != 3) {
            cout << ", ";
        }
    }
    cout << endl;
    cout << endl;
}

int getPlayerInput() {
    cout << "Your choice: ";
    string playerInput;
    std::getline(cin, playerInput);
    if (playerInput.size() == 1) {
        playerInput = tolower(playerInput.at(0));
        if (constants::CONTROLS.count(playerInput)) {
            return constants::CONTROLS.at(playerInput);
        }
    }
    return getPlayerInput();
}

void runEncounter(Player& playerCharacter, encounterSpawnData& spawnData) {
    if (spawnData.previousEncounter) {
        Encounter enemyEncounter(spawnData.encounterType, true, spawnData.previousStats);
    }
    else {
        Encounter enemyEncounter();
    }
}

void playerTryEntreDoor(Dungeon& playerDungeon, Player& playerCharacter, int playerChoice) {
    clearTerminal();
    constants::DIRECTION direction = static_cast<constants::DIRECTION>(playerChoice);
    DoorWall& side = playerDungeon.getRoom(playerDungeon.getPlayerCoordinate()).getSide(direction);
    vector<Item>& inventory = playerCharacter.getInventory();
    bool entreSuccess = side.getIsUnlocked();
    if (side.getWallHasDoor() && !entreSuccess) {//if wall is not just locked because no door
        for (int i = 0; i < inventory.size(); i++) {
            Item& RkeyProspect = inventory.at(i); 
            if (RkeyProspect.getType() == constants::key) {
                entreSuccess = side.tryUnlock((*static_cast<Key*>(&RkeyProspect)).getKeyType());
                if (entreSuccess) {
                    cout << "You used one " + RkeyProspect.getDisplayName() << ", \n";
                    inventory.erase(inventory.begin() + i);
                    break;
                }
            }
        }
    }
    if (entreSuccess) {
        encounterSpawnData& spawnData = playerDungeon.traverse(direction);
        if (spawnData.hasEncounter) {
            runEncounter(playerCharacter, spawnData);
        }
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
    int playerChoice = getPlayerInput();
    clearTerminal();
    if (playerChoice < 4) {
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
    playerDungeon.displayMap();
    cout << endl;
}

void play() {
    Player playerCharacter(20, 20);
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