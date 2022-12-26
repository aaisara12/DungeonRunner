#include "BattleSystem.h"
#include <stdio.h>
#include <time.h>
#include <string>

void BattleSystem::DeclareCharacterMove(BattleMove* battleMove, Character* source, std::list<Character*> targets)
{
	// TODO: Apply formatting to the action text based on source and targets
	updateBattleText(battleMove->actionText);
}

void BattleSystem::ResolveCharacterMove(BattleMove* battleMove, Character* source, Character* target)
{
	srand(time(NULL));
	int randomHitNumber = rand() % 100;
	int hitNumberThreshold = static_cast<int>(battleMove->accuracy * 100);
	if (randomHitNumber <= hitNumberThreshold)
	{
		int realDamage = target->takeDamage(battleMove->damage);
		std::string targetHitText = target->getName() + " takes " + std::to_string(realDamage) + " damage!";
		updateBattleText(targetHitText);
	}
}
