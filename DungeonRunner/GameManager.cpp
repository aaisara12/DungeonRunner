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
#include "InputOptionsUserInterface.h"
#include "TextDisplayUserInterface.h"
#include "Canvas.h"
#include "PartyUserInterface.h"


GameManager::GameManager(std::list<Character*> characters, InputReader * playerInputReader, InputReader * enemyInputReader)
	: characters(characters), currentState(nullptr)
{
	inputOptionsUserInterface = new InputOptionsUserInterface();
	optionSelector = new OptionSelector(inputOptionsUserInterface);

	optionSelector->getOnQueryCompletedEvent().addListener(this);

	// STATE INITIALIZATION

	exitState = new ExitGameState();

	// TODO: Implement some way of selecting the game characters to go into the battle
	// ASSUMPTION: ++ returns post-increment value
	std::vector<Character*> ally(++characters.begin(), characters.end());
	InputReader* allyInput = playerInputReader;
	std::vector<Character*> enemy(characters.begin(), ++characters.begin());
	InputReader* enemyInput = enemyInputReader;

	battleState = new BattleGameState(ally, enemy, allyInput, enemyInput, optionSelector);

	hubState = new MenuGameState(std::vector<std::pair<GameState*, std::string>>{{battleState, "Battle"}, {exitState, "Quit"}}, optionSelector, playerInputReader);

	// Initialize the user interfaces
	userInterfaces =
	{
		{hubState, std::list<UserInterface*> {new MainMenuUserInterface("DUNGEON RUNNER")}},
		{battleState, std::list<UserInterface*> {
			new PartyUserInterface(playerTeam),
			new TextDisplayUserInterface(dynamic_cast<BattleGameState*>(battleState)->getCurrentBattleTextChangedEvent())
		}},
		{exitState, std::list<UserInterface*>()}
	};

	// For stats tracking
	for (Character* member : ally)
	{
		playerTeam.addMemberToParty(member);
	}

	// Initialize start state
	currentState = hubState;
}

GameManager::~GameManager()
{
	// Even though GameManager owns this instance and will delete it anyways,
	// this is here for completeness
	optionSelector->getOnQueryCompletedEvent().removeListener(this);
	
	// Free state instances and their UIs
	for (const auto& pair : userInterfaces)
	{
		// Based on the assumption that no user interface instance appears twice
		// (which might result in memory being freed twice)
		for (UserInterface* userInterface : pair.second)
		{
			delete userInterface;
		}

		// State should only be freed after user interfaces since they depend
		// on the states still being allocated
		delete pair.first;
	}

	delete inputOptionsUserInterface;

	delete optionSelector;

}


void clear_screen(char fill = ' ');

void GameManager::start()
{
	//std::cout << "Game start!" << std::endl;

	// Run initial frame of UI
	for (UserInterface* ui : userInterfaces[currentState])
		std::cout << ui->getDisplay() << std::endl;

	// GOAL 1: Create a basic vertical slice where
	// the UI displays the health bar of the first
	// character in the list, and the battle system
	// asks the user every frame how much damage to
	// deal to the character. Once the character has
	// died, the battle system should terminate and
	// inform the game that the battle has concluded,
	// ultimately causing the game to terminate
	
	clock_t timeOfLastFrame = clock();

	// Flag for keeping track of whether a transition has just occurred.
	// Currently only used to determine whether screen should be refreshed or not
	bool didTransitionOccurLastFrame = false;

	// Initialize canvas
	Canvas canvas;
	refreshCanvasWithCurrentUserInterfaces(canvas);

	// Keep looping while there are still processes being run
	while (currentState != exitState)
	{
		// Update delta time for this frame
		float deltaTime = float(clock() - timeOfLastFrame) / CLOCKS_PER_SEC;

		timeOfLastFrame = clock();

		// Apply update for current frame
		
		if (didTransitionOccurLastFrame)
		{
			refreshCanvasWithCurrentUserInterfaces(canvas);
		}

		// Run the update for each process
		currentState->tick(deltaTime);

		// Fix the deltaTime after input request
		if (inputEventRaisedThisFrame)
		{
			inputEventRaisedThisFrame = false;

			// Reset clock since input resolution may take multiple seconds and throw off deltaTime for next frame
			timeOfLastFrame = clock();
		}

		didTransitionOccurLastFrame = false;
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

			didTransitionOccurLastFrame = true;
		}
	}
	
}

void GameManager::refreshCanvasWithCurrentUserInterfaces(Canvas& canvas)
{
	canvas.clearUserInterfaces();
	
	for (UserInterface* ui : userInterfaces[currentState])
	{
		canvas.loadUserInterface(ui);
	}
	canvas.refreshDisplay();

	canvas.loadUserInterface(inputOptionsUserInterface);		// This one doesn't belong to any particular state
}

void GameManager::onNotify(bool eventData)
{
	inputEventRaisedThisFrame = true;
}

