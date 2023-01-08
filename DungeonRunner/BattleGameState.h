#pragma once
#include "GameState.h"
#include "GameManager.h"
#include "Character.h"
#include "InputReader.h"
#include <list>
#include "Command.h"
#include "ObservableVariable.h"
#include "OptionSelector.h"

class Command;
class BattleGameState : public GameState
{
public:

	// DESIGN CHOICE: Dependency injection -- inject InputReader object
	// into battle process so that onus is on external scripts to
	// ensure a proper input reading module; this module does not have
	// to test input creation and can assume it works for its own tests.
	// This way, input creation logic does not need to clutter this process's code.
	BattleGameState(std::vector<Character*> characters, Character* boss, OptionSelector* optionSelector);

	virtual void tick(float deltaTime) override;

	virtual void onEnter() override;
	
	virtual void onExit() override;

	inline virtual bool isFinished() const override { return _isFinished; }

	inline virtual std::string getName() const override { return "Battle"; }

	inline Event<std::string>& getCurrentBattleTextChangedEvent() { return currentBattleText.getOnVariableChangedEvent(); }

	// COMMANDS
	// DESIGN CHOICE: Queue up command upon character defeat instead of subscribing
	// to defeat event so that BattleGameState does not need to become an observer,
	// which adds complexity and prevents it from responding to different events.
	// The whole point of events is to 1.) save computation resources by only
	// triggering the logic at select moments instead of continuously checking
	// and 2.) transfer dependency away from the broadcaster and onto the listeners.
	// This command is only called once every few seconds at most and thus changing
	// it to invoke upon hearing an event wouldn't really improve computation speed
	void evaluateBattleState();

	void endBattle();

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


	// Helper function for setting up the next round of moves for the characters
	// in the game
	void initializeCharacterActions();

	OptionSelector* optionSelector;

	// Text describing what's going on in the battle (used by UI)
	ObservableVariable<std::string> currentBattleText;

	// DESIGN CHOICE: Store characters in a vector since target selection 
	// is by index, and set of characters likely won't change frequently,
	// making a vector more optimal for this section
	std::vector<Character*> characters;

	// Boss character
	Character* boss;

	// Queue of current actions to happen in the battle
	std::list<DelayedCommand> queuedBattleCommands;

	bool _isFinished;
};
