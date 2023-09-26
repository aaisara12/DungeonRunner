#pragma once
#include <list>
#include "InputReader.h"
#include "Character.h"
#include "GameState.h"
#include "UserInterface.h"
#include "InputOptionsUserInterface.h"
#include "OptionSelector.h"
#include "Observer.h"
#include "Canvas.h"
#include "Party.h"

// DESIGN CHOICE: GameManager inherits from Observer so it can respond to
// input events. This implementation will need to change if there are
// multiple types of events that GameManager should listen for.

class GameManager : public Observer<bool>
{
public:
	GameManager(std::list<Character*> characters, InputReader* inputReader);

	~GameManager();

	// Start the game
	void start();

	// We choose not to make this a Canvas member function because its implementation is pretty specific to GameManager
	void refreshCanvasWithCurrentUserInterfaces(Canvas& canvas);

private:

	Party playerTeam;
	std::list<Character*> characters;
	
	OptionSelector* optionSelector;

	// Game States
	GameState* currentState;
	HubGameState* hubState;
	GameState* exitState;
	GameState* battleState;

	//std::list<UserInterface*>* activeUserInterfaces;
	std::unordered_map<GameState*, std::list<UserInterface*>> userInterfaces;
	InputOptionsUserInterface* inputOptionsUserInterface;

	bool inputEventRaisedThisFrame;

	// Free all memory associated with the active process and its UI
	//void cleanUpActiveProcess();

	

	// This is the event handler for input events
	virtual void onNotify(bool eventData);

};