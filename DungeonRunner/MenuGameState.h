#pragma once
#include "GameState.h"
#include "InputReader.h"
#include "GameManager.h"
#include "OptionSelector.h"

class MenuGameState : public HubGameState
{
public:
	MenuGameState(std::vector<std::pair<GameState*, std::string>> gameStatesAndDescriptions, OptionSelector* optionSelector);

	virtual void tick(float deltaTime) override;
	virtual void onEnter() override;

	inline virtual bool isFinished() const override { return _isFinished; };
	
	inline virtual GameState* getSelectedState() const override { return selectedState; };

	inline virtual std::string getName() const override { return "Main Menu"; }

private:
	OptionSelector* optionSelector;

	std::vector<GameState*> gameStates;
	std::vector<std::string> gameStateDescriptions;

	bool _isFinished;
	GameState* selectedState;
};