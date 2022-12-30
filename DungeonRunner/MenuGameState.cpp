#include "MenuGameState.h"

MenuGameState::MenuGameState(InputReader* inputReader, std::vector<std::pair<GameState*, std::string>> gameStatesAndDescriptions)
	:inputReader(inputReader), _isFinished(false), selectedState(nullptr)
{
	// DESIGN CHOICE: Pass in a pair of GameState* and string to ensure gameStates and gameStateDescriptions
	// have corresponding elements at the same index, which is important for the options selection part
	for (const std::pair<GameState*, std::string>& stateDescriptionPair : gameStatesAndDescriptions)
	{
		gameStates.push_back(stateDescriptionPair.first);
		gameStateDescriptions.push_back(stateDescriptionPair.second);
	}
}

void MenuGameState::tick(float deltaTime)
{
	// Here we assume that the descriptions are in the exact same order as their
	// correpsonding states in gameStates

    uint8_t response = inputReader->requestInput("What would you like to do?", gameStateDescriptions);
	if (response >= gameStates.size())
		selectedState = this;			// Default go back to this state
	else
		selectedState = gameStates[response];

	_isFinished = true;
}

void MenuGameState::onEnter()
{
	selectedState = nullptr;
	_isFinished = false;
}

