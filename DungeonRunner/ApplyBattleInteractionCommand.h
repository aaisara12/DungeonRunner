#pragma once
#include "Command.h"
#include "BattleInteraction.h"
#include <string>


class BattleGameState;
class ApplyBattleInteractionCommand : public Command
{
public:

	// DESIGN CHOICE: Pass in an instance of BattleGameState so that the command has the ability
	// to trigger a check on the state of the battle and decide whether or not to end the game
	// after applying it
	ApplyBattleInteractionCommand(BattleInteraction battleInteraction, BattleGameState* battleGameState)
		: battleInteraction(battleInteraction), battleGameState(battleGameState)
	{}

	virtual std::list<Command*> Execute(ObservableVariable<std::string>& textOutput) override;

private:
	BattleInteraction battleInteraction;
	BattleGameState* battleGameState;
};