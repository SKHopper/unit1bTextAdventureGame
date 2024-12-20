#include "Lifeform.h"

//false if died
bool Lifeform::updateHealth(double change) {
    health += change;
    if (health > maxHealth) {
        health = maxHealth;
    }
    else if (health < 0) {
        health = 0;
    }
    return health;
}

void Lifeform::displayHealth() {
    cout << "Life: [";
    for (int i = 0; i < health; i++) {
        if (i) {
            cout << ".";
        }
        cout << "X";
    }
    for (int i = 0; i < maxHealth - health; i++) {
        cout << ". ";
    }
    cout << "]";
}
