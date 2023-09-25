#pragma once
#include "Command.h"
#include "Character.h"
#include <format>
class DescribeBattleInteractionCommand : public Command
{
public:
	DescribeBattleInteractionCommand(BattleInteraction battleInteraction)
		: battleInteraction(battleInteraction)
	{}

	// Inherited via Command
	virtual std::list<Command*> Execute(ObservableVariable<std::string>& textOutput) override
	{
		// We assume actionText has formatting characters to inject the combatant names
		std::string completeActionText = 
			std::vformat(
				battleInteraction.move->actionText, 
				std::make_format_args(
					battleInteraction.source->getName(), 
					battleInteraction.target->getName()));

		textOutput.set(completeActionText);
		return std::list<Command*>();
	}

private:
	BattleInteraction battleInteraction;
};