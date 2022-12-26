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
	// it can be dangerous. 
	void DeclareCharacterMove(BattleMove* battleMove, Character* source, std::list<Character*> targets);			
	
	// Figure out whether a move hits and with what damage
	// DESIGN CHOICE: Make caller pass in all information about the move instead of storing
	// it when it is first declared. While this means there's not guarantee that the
	// order of declare-resolve will be correct, it means we're able to store information
	// about the moves that need to be resolved on the stack, enabling moves to be
	// resolved recursively (resolving a move may trigger more moves to be added to the stack
	// which may need to be resolved before any of the move's sibllings).
	// Note that multi-target moves can simply be encoded as multiple ResolveCharacterMove
	// commands on the stack targeted at a different target
	void ResolveCharacterMove(BattleMove* battleMove, Character* source, Character* target);		

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

	// Setter that automatically invokes battle status changed event
	void updateBattleText(std::string newText);
};