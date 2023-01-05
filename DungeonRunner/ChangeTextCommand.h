#pragma once
#include <string>
#include "Command.h"
class ChangeTextCommand : public Command
{
public:
	ChangeTextCommand(std::string newText)
		: newText(newText)
	{}

	// Inherited via Command
	virtual std::list<Command*> Execute(ObservableVariable<std::string>& textOutput) override
	{
		textOutput.set(newText);
		return std::list<Command*>();
	}

private:
	std::string newText;
};