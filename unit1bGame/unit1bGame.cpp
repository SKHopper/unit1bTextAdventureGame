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
}

int getPlayerInput() {
    cout << "Action: ";

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

void displayEncounterOptions(bool isEnemyTurn) {
    if (isEnemyTurn) {
        cout << "React: [1]dodge, [2]block, [3]escape";
    }
    else {
        cout << "Act: [1]light attack, [2]heavy attack, [3]escape";
    }
}

bool playerTryEscape(Dungeon& playerDungeon) {
    bool didSucceed = false;
    if (randomWeightedBoolean(/*0.92*/0)) {
        playerDungeon.escape();
        didSucceed = true;
    }
    return didSucceed;
}

//based on .https://stackoverflow.com/a/21995693
//pass in auto steady_clock::now()
template <
    class result_t = milliseconds,
    class clock_t = steady_clock,
    class duration_t = milliseconds
> double getElapsedSeconds(
    time_point <
        clock_t, 
        duration_t
    > const& startTime
) {
    auto elapsedTime = duration_cast<result_t>(clock_t::now() - startTime);
    auto elapsedMilliseconds = elapsedTime.count();
    double elapsedSeconds = static_cast<double>(elapsedMilliseconds) / 1000;

    return elapsedSeconds;
}

//TODO: replace with some lib func
void pause(double pauseDurationSeconds) {
    auto startTime = steady_clock::now();
    while (getElapsedSeconds(startTime) < pauseDurationSeconds) {}
}

bool playerEncounterAct(
    Player& playerCharacter, 
    Encounter& enemyEncounter, 
    Dungeon& playerDungeon,
    bool isEnemyTurn = false,
    Attack enemyAttack = {false, 0}
) {
    auto startTime = steady_clock::now();
    bool encounterEnd = false;
    int playerInput = 0;

    while (playerInput < 4 || playerInput > 6) {
        playerInput = getPlayerInput();
    }

    double elapsedSeconds = getElapsedSeconds(startTime);
    double elapsedSecondsResultMultiplier = getElapsedSecondsResultMultiplier(elapsedSeconds);

    switch (playerInput) {
    case 4:
        if (isEnemyTurn) {//dodge
            if (randomWeightedBoolean(0.5 * elapsedSecondsResultMultiplier)) {
                enemyAttack.dmg = 0;
            }
        }
        else {//light attack
            
        }
        break;
    case 5:
        if (isEnemyTurn) {//block
            if (randomWeightedBoolean(((enemyAttack.isHeavy) ? 0.2 : 1.2) * elapsedSecondsResultMultiplier)) {
                enemyAttack.dmg *= 0.1;
            }
        }
        else {//heavy attack

        }
        break;
    case 6://escape
        encounterEnd = playerTryEscape(playerDungeon);
        break;
    default://erroneous
        break;
    }
    
    playerCharacter.updateHealth(enemyAttack.dmg);

    return encounterEnd;
}

void runEncounter(Player& playerCharacter, encounterSpawnData spawnData, Dungeon& playerDungeon) {

    Encounter enemyEncounter(spawnData.encounterType, not spawnData.previousEncounter, spawnData.previousStats);
    clearTerminal();
    enemyEncounter.exposite();
    pause(3);

    while (true) {//combat turn loop
        clearTerminal();
        enemyEncounter.exposite();
        cout << endl << endl;
        playerCharacter.displayHealth();
        cout << endl << endl;
        Attack enemyAttack = enemyEncounter.attackPlayer();
        cout << endl << endl;
        displayEncounterOptions(true);
        
        cout << endl;
        if (playerEncounterAct(playerCharacter, enemyEncounter, playerDungeon, true, enemyAttack)) {
            break;
        }
        clearTerminal();
        enemyEncounter.exposite();
        cout << endl << endl;
        playerCharacter.displayHealth();
        cout << endl << endl;
        displayEncounterOptions(false);
        if (playerEncounterAct(playerCharacter, enemyEncounter, playerDungeon)) {
            break;
        }
    }

    clearTerminal();

    if (playerCharacter.getHealth()) {
        if (enemyEncounter.getHealth()) {//player escaped encounter
            cout << "Escaped the " << enemyEncounter.getDisplayName() << ", I'm headed to the last room." << endl;
        }
        else {//player killed encounter
            
        }
    }
    else {//encounter killed player

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
                    cout << "I used one " + RkeyProspect.getDisplayName() << ", \n";
                    inventory.erase(inventory.begin() + i);
                    break;
                }
            }
        }
    }
    if (entreSuccess) {
        encounterSpawnData spawnData = playerDungeon.traverse(direction);
        if (spawnData.hasEncounter) {
            runEncounter(playerCharacter, spawnData, playerDungeon);
        }
    }
    else {//display traversal fail msg
        if (side.getWallHasDoor()) {
            cout << "My satchel does not contain the rune to open the " << constants::DIRECTION_DISPLAY_NAME.at(direction) << " door";
        }
        else {
            cout << "The wall to the " << constants::DIRECTION_DISPLAY_NAME.at(direction) << " is impassable";
        }
        cout << ", the path is blocked." << endl;
    }
}

void playerAct(Dungeon& playerDungeon, Player& playerCharacter) {
    DungeonRoom& playerRoom = playerDungeon.getRoom(playerDungeon.getPlayerCoordinate());
    int playerChoice = getPlayerInput();
    clearTerminal();
    if (playerChoice < 4) {
        playerTryEntreDoor(playerDungeon, playerCharacter, playerChoice);
    }
    //elseifs other choices
}

//call room and player to display refreshed info
void exposite(Dungeon playerDungeon, Player playerCharacter) {
    playerDungeon.getRoom(playerDungeon.getPlayerCoordinate()).exposit();
    cout << endl;
    playerCharacter.exposite();
    cout << endl;
    cout << endl;
    playerDungeon.displayMap();
}

void play() {
    Player playerCharacter(20, 20);
    Dungeon playerDungeon;

    playerDungeon.makeStartRoom();

    while (true) {
        exposite(playerDungeon, playerCharacter);
        cout << endl;
        displayRoomOptions(playerCharacter);
        cout << endl;
        cout << endl;
        playerAct(playerDungeon, playerCharacter);
    }
}

int main() {
    //new seed per execute
    srand(time(0));

    play();
}