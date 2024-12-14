#include <iostream>

#include "Dungeon.h"
#include "player.h"

void displayRoomMenu(DungeonRoom room) {
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

void play(Dungeon& playerDungeon) {
    while (true) {
        playerDungeon.getRoom(playerDungeon.getPlayerCoordinate()).exposit();
        cout << endl;
        displayRoomMenu(playerDungeon.getRoom(playerDungeon.getPlayerCoordinate()));
        cout << endl;
        getPlayerInput(4);
    }
}

int main() {
    //new seed per execute
    srand(time(0));
    Dungeon playerDungeon;
    playerDungeon.makeStartRoom();
    play(playerDungeon);
}