#include "MenuGameState.h"

MenuGameState::MenuGameState(InputReader* inputReader, std::unordered_map<char, GameState*> gameStatesByCharacterRepresentation)
	:inputReader(inputReader), gameStatesByCharacterRepresentation(gameStatesByCharacterRepresentation),
	_isFinished(false), selectedState(nullptr), inputOptionsString("")
{
	for (auto pair : gameStatesByCharacterRepresentation)
	{
		inputOptionsString.push_back(pair.first);
	}
}

void MenuGameState::tick(float deltaTime)
{
    char response = inputReader->getInput("What would you like to do?", inputOptionsString);
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

