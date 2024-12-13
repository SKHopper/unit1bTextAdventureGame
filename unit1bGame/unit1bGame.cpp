#include <iostream>

#include "Dungeon.h"

static void loop() {
    
}

int main(){
    //new seed per execute
    srand(time(0));
    Dungeon mainDungeon;
    DungeonRoom testRoom = mainDungeon.makeStartRoom();
    testRoom.exposit();
    loop();
}