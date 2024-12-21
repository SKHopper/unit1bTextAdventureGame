#include <iostream>

#include "Dungeon.h"
#include "Player.h"
#include "Encounter.h"

void displayRoomOptions(Player& RplayerCharacter) {
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
    if (randomWeightedBoolean(1 - BASE_ESCAPE_CHANCE)) {
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

void displayCombatMsg(string combatMsg) {
    clearTerminal();
    cout << combatMsg;
    pause(1.4);
}

bool playerEncounterAct(
    Player& RplayerCharacter, 
    Encounter& RenemyEncounter, 
    Dungeon& RplayerDungeon,
    bool isEnemyTurn = false,
    Attack enemyAttack = {false, 0}
) {
    auto startTime = steady_clock::now();
    bool encounterEnd = false;
    int playerInput = 0;
    Attack playerAttack = {false, 0};
    string resultMsg = "";

    while (playerInput < 4 || playerInput > 6) {
        playerInput = getPlayerInput();
    }

    double elapsedSeconds = getElapsedSeconds(startTime);
    double elapsedSecondsResultMultiplier = getElapsedSecondsResultMultiplier(elapsedSeconds);

    switch (playerInput) {
    case 4:
        if (isEnemyTurn) {//dodge
            resultMsg = "Failed to dodge!";
            if (randomWeightedBoolean(1 - BASE_DODGE_CHANCE * elapsedSecondsResultMultiplier)) {
                enemyAttack.dmg = DODGED_ATTACK_DAMAGE;
                resultMsg = "Dodge succesful!";
            }
        }
        else {//light attack
            playerAttack = {false, BASE_PLAYER_LIGHT_ATTACK_DMG * elapsedSecondsResultMultiplier};
            resultMsg = (playerAttack.dmg) ? "Direct hit!" : "Too slow!";
        }
        break;
    case 5:
        if (isEnemyTurn) {//block
            resultMsg = "Failed to block!";
            if (randomWeightedBoolean(1 - ((enemyAttack.isHeavy) ? BASE_HEAVY_BLOCK_CHANCE : BASE_LIGHT_BLOCK_CHANCE) * elapsedSecondsResultMultiplier)) {
                enemyAttack.dmg *= BASE_BLOCK_DAMAGE_MULTIPLIER;
                resultMsg = "Block succesful!";
            }
        }
        else {//heavy attack
            playerAttack = {true, BASE_PLAYER_HEAVY_ATTACK_DMG * elapsedSecondsResultMultiplier};
            resultMsg = (playerAttack.dmg) ? "Direct hit!" : "Too slow!";
        }
        break;
    case 6://escape
        encounterEnd = playerTryEscape(RplayerDungeon);
        resultMsg = (encounterEnd) ? "Escaped!" : "Failed to escape";
        break;
    default://erroneous
        break;
    }
    
    if (not encounterEnd) {//not escaped
        if (isEnemyTurn) {
            encounterEnd = not RplayerCharacter.updateHealth(enemyAttack.dmg);
        }
        else {
            encounterEnd = not RenemyEncounter.updateHealth(playerAttack.dmg);
        }
    }

    displayCombatMsg(resultMsg);
    return encounterEnd;
}

Attack combatExposite(Player& RplayerCharacter, Encounter& RenemyEncounter, bool isEnemyTurn = false) {
    Attack enemyAttack = {false, 0};
    clearTerminal();

    RplayerCharacter.displayHealth();
    cout << endl << endl;

    RenemyEncounter.exposite();           cout << RenemyEncounter.getHealth();
    cout << endl << endl;

    if (isEnemyTurn) {
        enemyAttack = RenemyEncounter.attackPlayer();
    }
    cout << endl << endl;

    displayEncounterOptions(isEnemyTurn);
    cout << endl;

    return enemyAttack;
}

void killPlayer(Player& RplayerCharacter, Dungeon& RplayerDungeon) {
    RplayerDungeon.setPlayerCoordinate({0, 0});
    RplayerCharacter.die();
    clearTerminal();
    cout << "Out of life, escaped to my Return Rune.";
    pause(1.7);
};

void runEncounter(Player& RplayerCharacter, encounterSpawnData spawnData, Dungeon& RplayerDungeon) {
    DungeonRoom& RencounterRoom = RplayerDungeon.getRoom(RplayerDungeon.getPlayerCoordinate());
    Encounter enemyEncounter(spawnData.encounterType, not spawnData.previousEncounter, spawnData.previousStats);
    Attack enemyAttack;
    clearTerminal();
    enemyEncounter.exposite();
    pause(3);

    while (true) {//combat turn loop
        enemyAttack = combatExposite(RplayerCharacter, enemyEncounter,true);
        if (playerEncounterAct(RplayerCharacter, enemyEncounter, RplayerDungeon, true, enemyAttack)) {
            break;
        }

        combatExposite(RplayerCharacter, enemyEncounter);
        if (playerEncounterAct(RplayerCharacter, enemyEncounter, RplayerDungeon)) {
            break;
        }
    }

    clearTerminal();

    if (RplayerCharacter.getHealth()) {
        if (enemyEncounter.getHealth()) {//player escaped encounter
            cout << "Escaped the " << enemyEncounter.getDisplayName() << ", I'm headed back to the last room." << endl;
        }
        else {//player killed encounter
            RencounterRoom.killEncounter();
        }
    }
    else {//encounter killed player
        killPlayer(RplayerCharacter, RplayerDungeon);
    }
}

void playerTryEntreDoor(Dungeon& RplayerDungeon, Player& RplayerCharacter, int playerChoice) {
    clearTerminal();

    constants::DIRECTION direction = static_cast<constants::DIRECTION>(playerChoice);
    DoorWall& Rside = RplayerDungeon.getRoom(RplayerDungeon.getPlayerCoordinate()).getSide(direction);
    vector<Item>& inventory = RplayerCharacter.getInventory();
    bool entreSuccess = Rside.getIsUnlocked();

    if (Rside.getWallHasDoor() && !entreSuccess) {//if wall is not just locked because no door
        for (int i = 0; i < inventory.size(); i++) {
            Item& RkeyProspect = inventory.at(i); 
            if (RkeyProspect.getType() == constants::key) {
                entreSuccess = Rside.tryUnlock((*static_cast<Key*>(&RkeyProspect)).getKeyType());
                if (entreSuccess) {
                    cout << "I used one " + RkeyProspect.getDisplayName() << ", \n";
                    inventory.erase(inventory.begin() + i);
                    break;
                }
            }
        }
    }
    if (entreSuccess) {
        encounterSpawnData spawnData = RplayerDungeon.traverse(direction);
        if (spawnData.hasEncounter) {
            runEncounter(RplayerCharacter, spawnData, RplayerDungeon);
        }
    }
    else {//display traversal fail msg
        if (Rside.getWallHasDoor()) {
            cout << "My satchel does not contain the rune to open the " << constants::DIRECTION_DISPLAY_NAME.at(direction) << " door";
        }
        else {
            cout << "The wall to the " << constants::DIRECTION_DISPLAY_NAME.at(direction) << " is impassable";
        }
        cout << ", the path is blocked." << endl;
    }
}

void playerAct(Dungeon& RplayerDungeon, Player& RplayerCharacter) {
    int playerChoice = getPlayerInput();
    clearTerminal();
    if (playerChoice < 4) {
        playerTryEntreDoor(RplayerDungeon, RplayerCharacter, playerChoice);
    }
    //TODO: elseifs other choices
}

//call room and player to display refreshed info
void exposite(Dungeon& RplayerDungeon, Player& RplayerCharacter) {
    RplayerDungeon.getRoom(RplayerDungeon.getPlayerCoordinate()).exposit();
    cout << endl;
    RplayerCharacter.exposite();
    cout << endl;
    cout << endl;
    RplayerDungeon.displayMap();
}

void play() {
    Player playerCharacter(BASE_PLAYER_MAX_HEALTH, BASE_PLAYER_MAX_HEALTH);
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