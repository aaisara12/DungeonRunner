#pragma once
#include "Command.h"
#include "Character.h"

// Command for describing the state of the given character. It's typically used
// for informing the player the end state of a character after applying all effects
// related to the move performed on the character.
class EvaluateCharacterStateCommand : public Command
{
public:
	EvaluateCharacterStateCommand(Character* character)
		:character(character)
	{}

	inline virtual std::list<Command*> Execute(ObservableVariable<std::string>& textOutput) override
	{
		if (character->getStats()[Character::StatType::CUR_HP] <= 0)
			textOutput.set(character->getName() + " has been defeated.");
		else
			textOutput.set("");

		return std::list<Command*>();
	}

private:
	Character* character;
};