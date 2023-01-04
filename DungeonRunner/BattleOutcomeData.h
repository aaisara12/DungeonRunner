#pragma once
#include "BattleInteraction.h"
#include <list>

// Class for storing information about what happened
// as a result of applying a particular battle interaction
struct BattleOutcomeData
{
public:
	bool isHit;
	bool isDefeated;
	int damageTaken;
	int healingReceived;

	std::list<BattleInteraction> generatedInteractions;

	BattleOutcomeData()
		: isHit(false), isDefeated(false), damageTaken(0), healingReceived(0)
	{}
};