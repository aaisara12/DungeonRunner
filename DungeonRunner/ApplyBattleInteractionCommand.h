#pragma once
#include "Command.h"
#include "BattleInteraction.h"
#include <string>
class ApplyBattleInteractionCommand : public Command
{
public:
	ApplyBattleInteractionCommand(BattleInteraction battleInteraction)
		: battleInteraction(battleInteraction)
	{}

	virtual std::list<Command*> Execute(ObservableVariable<std::string>& textOutput) override;

private:
	BattleInteraction battleInteraction;
};