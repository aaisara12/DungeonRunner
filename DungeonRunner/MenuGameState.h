#pragma once
#include "GameState.h"
#include "InputReader.h"
#include "GameManager.h"
class MenuGameState : public HubGameState
{
public:
	MenuGameState(InputReader* inputReader, std::unordered_map<char, GameState*> gameStatesByCharacterRepresentation);

	virtual void tick(float deltaTime) override;
	virtual void onEnter() override;

	inline virtual bool isFinished() const override { return _isFinished; };
	
	inline virtual GameState* getSelectedState() const override { return selectedState; };

private:
	InputReader* inputReader;
	std::unordered_map<char, GameState*> gameStatesByCharacterRepresentation;

	std::string inputOptionsString;

	bool _isFinished;
	GameState* selectedState;
};