#pragma once
#include <list>
#include "BattleSystem.h"

struct DelayedCommand;

class Command
{
public:
	virtual ~Command() {}

	// Pass in the queue after execution to give command opportunity
	// to add more commands to the queue
	// DESIGN CHOICE: Pass in an instance to a BattleSystem instead of
	// data memebers of BattleSystem. While you do lose reusability in
	// a sense since you're forced to use it only on BattleSystems,
	// that's really the only object we'll be using it on. Additionally,
	// we get the benefit of keeping Commands lightweight and 
	// simple to understand.
	virtual void Execute(BattleSystem* battleSystem) = 0;
};

// DESGIN CHOICE: Separate data structure to pair a command ptr variable
// with a time remaining variable to make it easier to 
// read code when accessing these values
struct DelayedCommand
{
	float timeRemaining;
	Command* command;

	DelayedCommand(float delay, Command* command)
		: timeRemaining(delay), command(command)
	{}
};