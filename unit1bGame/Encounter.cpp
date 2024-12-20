#include "Encounter.h"

Attack Encounter::attackPlayer() {
	bool isHeavy = randomWeightedBoolean(1 - stats.heavyAttackChance);
	if (isHeavy) {
		cout << "Heavy attack! The " << stats.encounterDisplayName << " " << stats.heavyAttackDisplayMsg;
	}
	else {
		cout << "Light attack. The " << stats.encounterDisplayName << " " << stats.lightAttackDisplayMsg;
	}
	return {isHeavy, (isHeavy) ? stats.heavyAttackDmg : stats.lightAttackDmg};
}

void Encounter::exposite() {
	cout << "There's a " << getDisplayName() << " in this chamber!" << endl;
	cout << stats.description << endl;
}

string Encounter::getDisplayName() {
	return constants::ENCOUNTER_LEVEL_DISPLAY_NAME.at(stats.level) + " " + stats.encounterDisplayName;
}
