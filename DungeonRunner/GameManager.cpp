#include <iostream>
#include <list>
#include <ctime>
#include "GameManager.h"
#include "UserInterface.h"
#include "Character.h"
#include "GameState.h"
#include "MenuGameState.h"
#include "BattleGameState.h"
#include "ExitGameState.h"
#include "MainMenuUserInterface.h"
#include <Windows.h>

GameManager::GameManager(std::list<Character*> characters, InputReader* inputReader)
	: characters(characters), inputReader(inputReader), currentState(nullptr), activeUserInterfaces(nullptr)
{
	exitState = new ExitGameState();
	battleState = new BattleGameState((characters.size() == 0 ? nullptr : characters.front()), inputReader);

	hubState = new MenuGameState(inputReader, std::unordered_map<char, GameState*>{
		{'q', exitState},
		{'p', battleState}
	});

	// Initialize the user interfaces
	userInterfaces =
	{
		{hubState, std::list<UserInterface*> {new MainMenuUserInterface("DUNGEON RUNNER")}},
		{battleState, std::list<UserInterface*> {}}
	};

	// Initialize start state
	currentState = hubState;
}


void clear_screen(char fill = ' ');

void GameManager::start()
{
	std::cout << "Game start!" << std::endl;

	// GOAL 1: Create a basic vertical slice where
	// the UI displays the health bar of the first
	// character in the list, and the battle system
	// asks the user every frame how much damage to
	// deal to the character. Once the character has
	// died, the battle system should terminate and
	// inform the game that the battle has concluded,
	// ultimately causing the game to terminate
	
	// TODO:
	// 0. Implement base functionality for UI framing
	// 1. Implement basic UI to go with the menu process (just like a diagram of your options)
	// 2. Implement simple battle process (single character, deal damage every turn)
	// 3. Implement basic UI to go with the battle process (just the health bar)
	
	clock_t timeOfLastFrame = clock();

	// Keep looping while there are still processes being run
	while (currentState != exitState)
	{
		// Update delta time for this frame
		float deltaTime = float(clock() - timeOfLastFrame) / CLOCKS_PER_SEC;
		timeOfLastFrame = clock();

		// Apply update for current frame
			
		// Display visuals for each process
		clear_screen();
		for (UserInterface* ui : userInterfaces[currentState])
			std::cout << ui->getDisplay() << std::endl;

		// Run the update for each process
		// DESIGN CHOICE: Run tick after UI display so that menu UI displays immediately
		// upon start up. While this choice was made just to resolve a specific case,
		// there aren't any drawbacks to this order as far as I can tell.
		currentState->tick(deltaTime);

		// Check for transitions
		// DESIGN CHOICE: Hard-code all states to transition back to the hub state once they
		// have finished (the only transition condition) and the hub state to transition to
		// the state selcted by the user instead of using an explicit transition table.
		// Due to the simplicity of the game structure, the overhead of a full-blown
		// state machine with state transition tables was not worth it.
		if (currentState->isFinished())
		{
			GameState* nextState = currentState == hubState ? hubState->getSelectedState() : hubState;

			currentState->onExit();
			currentState = nextState;
			currentState->onEnter();
		}
	}
	
}

void GameManager::cleanUpActiveProcess()
{
	if (activeUserInterfaces != nullptr)
	{
		for (UserInterface* ui : *activeUserInterfaces)
			delete ui;

		delete activeUserInterfaces;
	}
	
	if(currentState != nullptr)
		delete currentState;

	activeUserInterfaces = nullptr;
	currentState = nullptr;
}

#if defined(_WIN32)
#define PLATFORM_NAME "windows" // Windows
#elif defined(_WIN64)
#define PLATFORM_NAME "windows" // Windows
#endif
void clear_screen(char fill) {
	if (PLATFORM_NAME == "windows")
	{
		// This is a little function from:
		// https://stackoverflow.com/questions/5866529/how-do-we-clear-the-console-in-assembly/5866648#5866648

		COORD tl = { 0,0 };
		CONSOLE_SCREEN_BUFFER_INFO s;
		HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
		GetConsoleScreenBufferInfo(console, &s);
		DWORD written, cells = s.dwSize.X * s.dwSize.Y;
		FillConsoleOutputCharacter(console, fill, cells, tl, &written);
		FillConsoleOutputAttribute(console, s.wAttributes, cells, tl, &written);
		SetConsoleCursorPosition(console, tl);
	}
}

