#include "ApplyBattleInteractionCommand.h"
#include "DescribeBattleInteractionCommand.h"
#include "Character.h"
#include <time.h>

std::list<Command*> ApplyBattleInteractionCommand::Execute(ObservableVariable<std::string>& textOutput)
{
	std::string outcomeText;
	std::list<Command*> generatedCommands;

	BattleMove* selectedMove = battleInteraction.move;

	srand(time(NULL));
	int randomHitNumber = rand() % 100;
	int hitNumberThreshold = static_cast<int>(selectedMove->accuracy * 100);
	if (randomHitNumber <= hitNumberThreshold)
	{
		std::list<BattleInteraction> generatedInteractions = battleInteraction.target->applyBattleInteraction(battleInteraction);

		// TODO: Design a less expensive solution to generating new commands
		for (BattleInteraction interaction : generatedInteractions)
		{
			generatedCommands.push_back(new DescribeBattleInteractionCommand(interaction));
			generatedCommands.push_back(new ApplyBattleInteractionCommand(interaction));
		}

		// TODO: Design way to get information about the damage dealt after def calculations
		int realDamage = battleInteraction.move->damage;

		outcomeText = battleInteraction.target->getName() + " takes " + std::to_string(realDamage) + " damage!";
	}
	else
		outcomeText = battleInteraction.source->getName() + " misses!";

	textOutput.set(outcomeText);
    return generatedCommands;
}
