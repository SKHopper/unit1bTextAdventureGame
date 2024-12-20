#pragma once

#include "utilities.h"

class Lifeform {
	double maxHealth = 20;
	double health = maxHealth;
public:
	Lifeform(double newMaxHealth, double newHealth) : maxHealth(newMaxHealth), health(newHealth) {};
	bool updateHealth(double change);
	void displayHealth();
};