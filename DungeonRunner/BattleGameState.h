#pragma once
#include "GameState.h"
#include "Character.h"
#include "InputReader.h"

class BattleGameState : public GameState
{
public:

	// DESIGN CHOICE: Dependency injection -- inject InputReader object
	// into battle process so that onus is on external scripts to
	// ensure a proper input reading module; this module does not have
	// to test input creation and can assume it works for its own tests.
	// This way, input creation logic does not need to clutter this process's code.
	BattleGameState(Character* boss, InputReader* inputReader);
	virtual void tick(float deltaTime) override;

	inline virtual bool isFinished() const override { return _isFinished; }

private:
	Character* boss;
	InputReader* inputReader;
	std::string currentBattleText;

	bool _isFinished;
};
