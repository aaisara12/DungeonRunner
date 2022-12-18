#include <iostream>
#include <list>
#include <ctime>
#include "GameManager.h"
#include "UserInterface.h"
#include "Character.h"
#include "Process.h"
#include "MenuProcess.h"
#include "MainMenuUserInterface.h"

GameManager::GameManager(std::list<Character*> characters, InputReader* inputReader)
	: characters(characters), inputReader(inputReader)
{
}

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

	// Add the start up process
	addProcess(new MenuProcess(inputReader, *this), new std::list<UserInterface*>{new MainMenuUserInterface("DUNGEON RUNNER")});

	clock_t timeOfLastFrame = clock();

	// Keep looping while there are still processes being run
	while (activeProcesses.size() > 0)
	{
		// Update delta time for this frame
		float deltaTime = float(clock() - timeOfLastFrame) / CLOCKS_PER_SEC;
		timeOfLastFrame = clock();

		// Apply update for current frame
		for (std::list<Process*>::iterator processIterator = activeProcesses.begin(); processIterator != activeProcesses.end();)
		{
			Process* process = (*processIterator);
			process->tick(deltaTime);

			// Display visuals for each process
			for (UserInterface* ui : *processToUserInterfaces[process])
				std::cout << ui->getDisplay() << std::endl;

			// Clean up process and associated UI once it's finished
			if (process->isFinished())
			{
				for (UserInterface* ui : *processToUserInterfaces[process])
					delete ui;

				delete processToUserInterfaces[process];

				processToUserInterfaces.erase(process);

				delete process;

				processIterator = activeProcesses.erase(processIterator);
			}
			else
				processIterator++;
		}

	}
	
}

void GameManager::addProcess(Process* process, std::list<UserInterface*>* processUserInterfaces)
{
	activeProcesses.push_back(process);
	processToUserInterfaces[process] = processUserInterfaces;
}
