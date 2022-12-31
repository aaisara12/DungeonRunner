#pragma once
#include "GameState.h"
#include "InputReader.h"
#include "GameManager.h"
class MenuGameState : public HubGameState
{
public:
	MenuGameState(GameManager* gameManager, std::vector<std::pair<GameState*, std::string>> gameStatesAndDescriptions);

	virtual void tick(float deltaTime) override;
	virtual void onEnter() override;

	inline virtual bool isFinished() const override { return _isFinished; };
	
	inline virtual GameState* getSelectedState() const override { return selectedState; };

private:
	GameManager* gameManager;

	std::vector<GameState*> gameStates;
	std::vector<std::string> gameStateDescriptions;

	bool _isFinished;
	GameState* selectedState;
};