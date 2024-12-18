#include "Encounter.h"

attack Encounter::attackPlayer() {
	bool isHeavy = randomWeightedBoolean(1 - stats.heavyAttackChance);
	if (isHeavy) {
		cout << "Heavy attack! The " << stats.encounterDisplayName << " " << stats.heavyAttackDisplayMsg;
	}
	else {
		cout << "Light attack. The " << stats.encounterDisplayName << " " << stats.lightAttackDisplayMsg;
	}
	return {isHeavy, (isHeavy) ? stats.heavyAttackDmg : stats.lightAttackDmg};
}
