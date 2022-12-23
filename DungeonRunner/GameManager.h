#pragma once
#include<list>
#include "InputReader.h"
#include "Character.h"
#include "GameState.h"
#include "UserInterface.h"

class GameManager
{
public:
	GameManager(std::list<Character*> characters, InputReader* inputReader);

	// Start the game
	void start();

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



	// Free all memory associated with the active process and its UI
	void cleanUpActiveProcess();
};