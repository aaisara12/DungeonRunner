#include "MenuGameState.h"

MenuGameState::MenuGameState(std::vector<std::pair<GameState*, std::string>> gameStatesAndDescriptions, OptionSelector* optionSelector)
	:_isFinished(false), selectedState(nullptr), optionSelector(optionSelector)
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

	// TODO: Figure out how to eventually get input back to the caller
	// uint8_t response = gameManager->requestInput("What would you like to do?", gameStateDescriptions);
	//if (response >= gameStates.size())
	//	selectedState = this;			// Default go back to this state
	//else
	//	selectedState = gameStates[response];

	selectedState = optionSelector->queryOptions("What would you like to do?", gameStates);

	_isFinished = true;
}

void MenuGameState::onEnter()
{
	selectedState = nullptr;
	_isFinished = false;
}

