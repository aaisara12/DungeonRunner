#pragma once
#include "CharacterLoader.h"
class DummyCharacterLoader : public CharacterLoader
{
public:
	virtual std::list<Character*> getCharacters()
	{
		BattleMove* whiffMove = new BattleMove("Kick", 25, 0, 1.0f, 0, "{0} kicks {1} in the shins!", BattleMove::ENEMY);
		BattleMove* punchMove = new BattleMove("Punch", 10, 0, 1.0f, 1, "{0} throws a fist at {1}!", BattleMove::ENEMY);
		BattleMove* healMove = new BattleMove("Heal", 0, 4, 1, 2, "{0} glows with purity!", BattleMove::ALLY);

		std::vector<BattleMove*> moveset1 = { punchMove, healMove };
		std::vector<BattleMove*> moveset2 = { whiffMove, healMove };

		std::unordered_map<Character::StatType, int> stats1
		{
			{Character::CUR_HP, 100},
			{Character::MAX_HP, 100},
			{Character::DEF, 1},
			{Character::ATK, 1},
			{Character::HEAL, 3}
		};
		std::unordered_map<Character::StatType, int> stats2
		{
			{Character::CUR_HP, 40},
			{Character::MAX_HP, 40},
			{Character::DEF, 0},
			{Character::ATK, 4},
			{Character::HEAL, 2}
		};

		return std::list<Character*>{new Character("Anduin", moveset1, stats1), new Character("Gul'dan", moveset2, stats2)};
	}
};