#include <iostream>

#include "Dungeon.h"

static void loop() {
    
}

int main(){
    //new seed per execute
    srand(time(0));
    Dungeon playerDungeon;
    playerDungeon.makeStartRoom();
    playerDungeon.getRoomMap().at(0).room.exposit();
    playerDungeon.traverse(constants::north); 
    playerDungeon.getRoomMap().at(1).room.exposit(); 
    loop();
}