#pragma once
#include <functional>
#include <list>
#include "BattleInteraction.h"
#include "BattleOutcomeData.h"
#include "Character.h"

struct BattleEffect
{
	// Predicate for checking whether the effect should occur
	std::function<bool(BattleOutcomeData outcome, Character* source, Character* target)> condition;

	// Function for generating the resulting interactions caused by the effect
	std::function<std::list<BattleInteraction>(Character* source, Character* target)> interactionsGenerator;
};