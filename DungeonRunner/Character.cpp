#include "Character.h"
#include <time.h>

Character::Character(std::string name)
	:name(name)
{
	stats = std::unordered_map<StatType, int>
	{
		{StatType::MAX_HP, 10},
		{StatType::CUR_HP, 10},
		{StatType::ATK, 1},
		{StatType::DEF, 0}
	};
}

Character::Character(std::string name, std::unordered_map<StatType, int> stats)
	:name(name)
{
	this->stats = std::unordered_map<StatType, int>
	{
		{StatType::MAX_HP, stats.count(StatType::MAX_HP) != 0? stats[StatType::MAX_HP] : 0},
		{StatType::CUR_HP, stats.count(StatType::CUR_HP) != 0 ? stats[StatType::CUR_HP] : 0},
		{StatType::ATK, stats.count(StatType::ATK) != 0 ? stats[StatType::ATK] : 0},
		{StatType::DEF, stats.count(StatType::DEF) != 0 ? stats[StatType::DEF] : 0},
		{StatType::HEAL, stats.count(StatType::HEAL) != 0 ? stats[StatType::HEAL] : 0}
	};
}

Character::Character(std::string name, std::vector<BattleMove*> moves)
	:name(name), moves(moves)
{
	stats = std::unordered_map<StatType, int>
	{
		{StatType::MAX_HP, 10},
		{StatType::CUR_HP, 10},
		{StatType::ATK, 1},
		{StatType::DEF, 0}
	};
}

BattleOutcomeData Character::applyBattleInteraction(BattleInteraction battleInteraction)
{
	BattleOutcomeData data;

	srand(time(NULL));
	int randomHitNumber = rand() % 100;
	int hitNumberThreshold = static_cast<int>(battleInteraction.move->accuracy * 100);

	// Does the move land?
	if (randomHitNumber <= hitNumberThreshold)
	{
		int damageTaken = computeRealDamage(
				battleInteraction.source->getStats()[Character::ATK], 
				battleInteraction.target->getStats()[Character::DEF], 
				battleInteraction.move->damage);
		int healingReceived = computeHeal(battleInteraction.source->getStats()[Character::HEAL], battleInteraction.move->heal);

		// Apply health change to character
		stats[Character::CUR_HP] += healingReceived - damageTaken;
		if (stats[Character::CUR_HP] < 0)
			stats[Character::CUR_HP] = 0;
		if (stats[Character::CUR_HP] > stats[Character::MAX_HP])
			stats[Character::CUR_HP] = stats[Character::MAX_HP];


		data.isHit = true;
		data.damageTaken = damageTaken;
		data.healingReceived = healingReceived;

		// TODO: Run through all conditions and check for any interactions
		data.generatedInteractions = std::list<BattleInteraction>();
	}
	else
		data.isHit = false;

	return data;
}

int Character::computeRealDamage(int attackPower, int defendPower, int rawDamage)
{
	return std::max(attackPower - defendPower, 0) * rawDamage;
}

int Character::computeHeal(int healPower, int rawHeal)
{
	return healPower * rawHeal;
}
