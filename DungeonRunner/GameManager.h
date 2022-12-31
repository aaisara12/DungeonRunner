#pragma once
#include<list>
#include "InputReader.h"
#include "Character.h"
#include "GameState.h"
#include "UserInterface.h"
#include "InputOptionsUserInterface.h"

class GameManager
{
public:
	GameManager(std::list<Character*> characters, InputReader* inputReader);

	// Start the game
	void start();


	uint8_t requestInput(std::string query, std::vector<std::string> optionDescriptions);

private:

	std::list<Character*> characters;
	InputReader* inputReader;

	// Game States
	GameState* currentState;
	HubGameState* hubState;
	GameState* exitState;
	GameState* battleState;

	std::list<UserInterface*>* activeUserInterfaces;
	std::unordered_map<GameState*, std::list<UserInterface*>> userInterfaces;

	InputOptionsUserInterface* inputOptionsUserInterface;

	bool inputEventRaisedThisFrame;

	// Free all memory associated with the active process and its UI
	void cleanUpActiveProcess();

	
};