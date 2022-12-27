#pragma once
#include "GameState.h"
#include "Character.h"
#include "InputReader.h"
#include <list>
#include "Command.h"
#include "ObservableVariable.h"

class Command;
class BattleGameState : public GameState
{
public:

	// DESIGN CHOICE: Dependency injection -- inject InputReader object
	// into battle process so that onus is on external scripts to
	// ensure a proper input reading module; this module does not have
	// to test input creation and can assume it works for its own tests.
	// This way, input creation logic does not need to clutter this process's code.
	BattleGameState(std::list<Character*> characters, Character* boss, InputReader* inputReader);

	virtual void tick(float deltaTime) override;

	inline virtual bool isFinished() const override { return _isFinished; }


private:

	// DESIGN CHOICE: BattleGameState is a wrapper around a BattleSystem instead
	// of just implementing the battle functionality itself. Since BattleSystem
	// doesn't have a sense of time and reacts instantly to method calls,
	// it's easier to test than having to queue up commands and watch the output
	// once their delays have been satisfied. It feels like a cleaner separation
	// of responsibilities: the BattleSystem knows everything related to the
	// application of battle actions and how it affects the state of the battle,
	// and the BattleGameState knows everything related to when these battle
	// actions should be performed.
	//BattleSystem* battleSystem;



	InputReader* inputReader;

	// Text describing what's going on in the battle (used by UI)
	ObservableVariable<std::string> currentBattleText;

	// List of all characters in game, including boss
	std::list<Character*> characters;

	// Boss character
	Character* boss;

	// Queue of current actions to happen in the battle
	std::list<DelayedCommand> queuedBattleCommands;

	bool _isFinished;
};
