#pragma once
#include<list>
#include "InputReader.h"
#include "Character.h"
#include "Process.h"
#include "UserInterface.h"

class GameManager
{
public:
	GameManager(std::list<Character*> characters, InputReader* inputReader);

	// Start the game
	void start();

	// Add a process to be managed by this Game Manager. The Game Manager will now be
	// responsible for deallocating it and its user interfaces
	void setActiveProcess(Process* process, std::list<UserInterface*>* processUserInterfaces);

private:
	std::list<Character*> characters;
	InputReader* inputReader;

	Process* activeProcess;
	std::list<UserInterface*>* activeUserInterfaces;

	// Free all memory associated with the active process and its UI
	void cleanUpActiveProcess();
};