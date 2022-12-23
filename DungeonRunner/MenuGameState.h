#pragma once
#include "GameState.h"
#include "InputReader.h"
#include "GameManager.h"
class MenuGameState : public HubGameState
{
public:
	MenuGameState(InputReader* inputReader, std::unordered_map<char, GameState*> gameStatesByCharacterRepresentation)
		:inputReader(inputReader), gameStatesByCharacterRepresentation(gameStatesByCharacterRepresentation), 
		_isFinished(false), selectedState(nullptr)
	{}

	virtual void tick(float deltaTime) override;
	virtual void onEnter() override;

	inline virtual bool isFinished() const override { return _isFinished; };
	
	inline virtual GameState* getSelectedState() const override { return selectedState; };

private:
	InputReader* inputReader;
	std::unordered_map<char, GameState*> gameStatesByCharacterRepresentation;
	bool _isFinished;
	GameState* selectedState;
};