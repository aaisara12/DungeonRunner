#pragma once
#include "GameState.h"

// This is just a placeholder state so that the
// game knows when to exit and we don't have to
// handle any special cases in the logic.
class ExitGameState : public GameState
{
	inline virtual bool isFinished() const override { return false; }

	inline virtual std::string getName() const override { return "Exit"; }
};