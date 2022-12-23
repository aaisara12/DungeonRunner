#include "MenuGameState.h"

void MenuGameState::tick(float deltaTime)
{
    char response = inputReader->getInput("What would you like to do?", "pq");
	if (gameStatesByCharacterRepresentation.count(response) == 0)
		selectedState = this;
	else
		selectedState = gameStatesByCharacterRepresentation[response];

	_isFinished = true;
}

void MenuGameState::onEnter()
{
	selectedState = nullptr;
	_isFinished = false;
}

