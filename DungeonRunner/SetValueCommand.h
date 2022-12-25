#pragma once
#include "Command.h"

// Command to set a variable to a given value
// DESIGN CHOICE: Dangerous since value ref
// could possibly be deallocated by the time
// command is executed, but very efficient
template <typename T>
class SetValueCommand : public Command
{
public:
	SetValueCommand(T& valueRef, T newValue)
		: valueRef(valueRef), newValue(newValue)
	{}

	virtual void Execute(Command::CommandQueue commandQueue) override
	{
		valueRef = newValue;
	}
private:
	T& valueRef;
	T newValue;
};