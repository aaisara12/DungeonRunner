#pragma once
#include "Character.h"
#include "BattleMove.h"

class BattleSystem
{
public:
	BattleSystem(std::list<Character*> characters, Character* boss)
		: characters(characters), boss(boss), currentBattleText("")
	{}


	// DESIGN CHOICE: Separate battles into two phases: move declaration and move resolution.
	// This allows us to update the status text with the battle move action before getting the
	// result of the action. Another option could be to have a function that just directly
	// changes the status text, but then that would mean leaving up the responsibility for
	// changing the text in a defined way up to some external piece of logic, which means
	// it can be dangerous. It also ensures that the status text shows the move declaration
	// before showing any result (defined order).
	// Declare a move to be performed
	void DeclareCharacterMove(BattleMove* battleMove, Character* source, std::list<Character*> targets);			
	
	// Figure out whether the declared move hits and with what damage
	void ResolveCharacterMove();		

	// IDEA:
	// TryCharacterMove transitions BattleSystem to the "move attempt" phase, and the
	// status message changes. It's only after it gets the go ahead to resolve the attempt
	// that the "move" phase occurs and status message changes to "Character A missed!" or
	// "Boss blocked the attack!"

private:
	// Text describing what's going on in the battle (used by UI)
	std::string currentBattleText;

	// List of all characters in game, including boss
	std::list<Character*> characters;

	// Boss character
	Character* boss;
};