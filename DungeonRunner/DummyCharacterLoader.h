#pragma once
#include "CharacterLoader.h"
class DummyCharacterLoader : public CharacterLoader
{
public:
	virtual std::list<Character*> getCharacters()
	{
		BattleMove* whiffMove = new BattleMove("Whiff", 100, 0, 0.0f, 0, "{0} attempts to throw a punch at {1}", BattleMove::ENEMY);
		BattleMove* punchMove = new BattleMove("Punch", 10, 0, 1.0f, 1, "{0} throws a fist at {1}!", BattleMove::ENEMY);
		BattleMove* healMove = new BattleMove("Heal", 0, 20, 1, 2, "{0} glows with purity!", BattleMove::ALLY);

		std::vector<BattleMove*> moveset1 = { punchMove, healMove };
		std::vector<BattleMove*> moveset2 = { whiffMove, healMove };

		return std::list<Character*>{new Character("Anduin", moveset1), new Character("Gul'dan", moveset2)};
	}
};