#pragma once
#include "Command.h"
class DescribeBattleInteractionCommand : public Command
{
public:
	DescribeBattleInteractionCommand(BattleInteraction battleInteraction)
		: battleInteraction(battleInteraction)
	{}

	// Inherited via Command
	virtual std::list<Command*> Execute(ObservableVariable<std::string>& textOutput) override
	{
		// TODO: Apply formatting to the text to insert source and target names
		textOutput.set(battleInteraction.move->actionText);
		return std::list<Command*>();
	}

private:
	BattleInteraction battleInteraction;
};