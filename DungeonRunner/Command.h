#pragma once
#include <queue>

struct DelayedCommand;

class Command
{
public:
	virtual ~Command() {}

	// Pass in the queue after execution to give command opportunity
	// to add more commands to the queue
	virtual void Execute(std::queue<DelayedCommand>& commandQueue) = 0;
};

// DESGIN CHOICE: Separate data structure to pair a command ptr variable
// with a time remaining variable to make it easier to 
// read code when accessing these values
struct DelayedCommand
{
	float timeRemaining;
	Command* command;

	DelayedCommand()
		: timeRemaining(0), command(nullptr)
	{}
};