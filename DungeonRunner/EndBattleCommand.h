#pragma once
#include "Command.h"

// Command for forcibly ending the battle. This is typically used as a terminating command
// placed in the queue after the game has determined to be finished.
class BattleGameState;
class EndBattleCommand : public Command
{
public:
	EndBattleCommand(BattleGameState* battleGameState)
		:battleGameState(battleGameState)
	{}

private:
	BattleGameState* battleGameState;

	// Inherited via Command
	virtual std::list<Command*> Execute(ObservableVariable<std::string>& textOutput) override;
};