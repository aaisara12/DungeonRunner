#pragma once
#include <functional>
#include <list>
#include "BattleInteraction.h"
#include "BattleOutcomeData.h"
#include "Character.h"

struct BattleEffect
{
	// Predicate for checking whether the effect should occur
	// interaction is the BattleInteraction that results in the outcome
	std::function<bool(BattleOutcomeData outcome, BattleInteraction interaction)> condition;

	// Function for generating the resulting interactions caused by the effect
	std::function<std::list<BattleInteraction>(BattleInteraction interaction)> interactionsGenerator;
};