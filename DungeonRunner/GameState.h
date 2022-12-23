#pragma once
#include <list>
class GameState
{
public:
	virtual void tick(float deltaTime) {};
	virtual void onEnter() {}
	virtual void onExit() {}

	virtual bool isFinished() const = 0;
};

// DESIGN CHOICE: A special GameState that has the ability to
// select a particular state. The idea is that
// it will allow us some flexibility for swapping
// between different menu implementations at the
// start of the game.
class HubGameState : public GameState
{
public:
	virtual GameState* getSelectedState() const = 0;
};
