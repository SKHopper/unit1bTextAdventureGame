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
