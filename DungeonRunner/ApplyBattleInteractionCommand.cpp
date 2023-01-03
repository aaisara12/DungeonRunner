#include "ApplyBattleInteractionCommand.h"
#include "DescribeBattleInteractionCommand.h"
#include "Character.h"
#include <time.h>

std::list<Command*> ApplyBattleInteractionCommand::Execute(ObservableVariable<std::string>& textOutput)
{
	std::string outcomeText;
	std::list<Command*> generatedCommands;

	BattleOutcomeData outcome = battleInteraction.target->applyBattleInteraction(battleInteraction);

	// DESIGN CHOICE: Loop through const ref instead of copy constructing new BattleInteraction
	// to save on amount of copying
	for (const BattleInteraction& interaction : outcome.generatedInteractions)
	{
		generatedCommands.push_back(new DescribeBattleInteractionCommand(interaction));
		generatedCommands.push_back(new ApplyBattleInteractionCommand(interaction));
	}

	if (outcome.isHit)
	{
		if (outcome.damageTaken > 0)
			outcomeText = battleInteraction.target->getName() + " was hit for " + std::to_string(outcome.damageTaken) + " damage!";
		else if (outcome.healingReceived > 0)
			outcomeText = battleInteraction.target->getName() + " healed for " + std::to_string(outcome.healingReceived) + " points!";
		else
			outcomeText = "but nothing happened!";
	}
	else
		outcomeText = battleInteraction.source->getName() + " missed!";

	textOutput.set(outcomeText);
    return generatedCommands;
}
