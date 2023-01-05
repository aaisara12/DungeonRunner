#pragma once
#include "CharacterLoader.h"
class DummyCharacterLoader : public CharacterLoader
{
public:
	virtual std::list<Character*> getCharacters()
	{
		BattleMove* punchMove = new BattleMove("Punch", 10, 0, 1.0f, 1, "throws a fist!");
		BattleMove* healMove = new BattleMove("Heal", 0, 20, 1, 2, "glows with purity!");

		std::vector<BattleMove*> moveset1 = { punchMove, healMove };

		return std::list<Character*>{new Character("Anduin", moveset1), new Character("Gul'dan", moveset1)};
	}
};