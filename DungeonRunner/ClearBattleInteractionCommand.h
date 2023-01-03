#pragma once
#include "Command.h"
class ClearBattleInteractionCommand : public Command
{
	// Inherited via Command
	virtual std::list<Command*> Execute(ObservableVariable<std::string>& textOutput) override
	{
		textOutput.set("");
		return std::list<Command*>();
	}
};