#pragma once
#include "Command.h"

// Command for triggering BattleGameState's evaluateBattleState method, which is intended
// to check whether the game should be terminated or not, and if so, prepare the game to end
class BattleGameState;
class EvaluateBattleStateCommand : public Command
{
public:
	EvaluateBattleStateCommand(BattleGameState* battleGameState)
		: battleGameState(battleGameState)
	{}

private:
	BattleGameState* battleGameState;

	// Inherited via Command
	virtual std::list<Command*> Execute(ObservableVariable<std::string>& textOutput) override;
};