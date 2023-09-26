#pragma once
#include "CharacterLoader.h"
class DummyCharacterLoader : public CharacterLoader
{
public:
	virtual std::vector<Character*> getCharacters()
	{
		BattleMove* kickMove = new BattleMove("Kick", 25, 0, 1.0f, 0, "{0} kicks {1} in the shins!", BattleMove::ENEMY);
		BattleMove* punchMove = new BattleMove("Punch", 10, 0, 1.0f, 1, "{0} throws a fist at {1}!", BattleMove::ENEMY);
		BattleMove* slashMove = new BattleMove("Slash", 5, 0, 1.0f, 1, "{0} brings a mighty sword down upon {1}!", BattleMove::ENEMY);
		BattleMove* shadowBoltMove = new BattleMove("Shadow Bolt", 50, 0, 1.0f, 3, "{0} summons a swirling mass of dark energy and hurls it towards {1}'s chest!", BattleMove::ENEMY);
		BattleMove* healMove = new BattleMove("Heal", 0, 4, 1, 2, "{0} glows with purity!", BattleMove::ALLY);

		std::vector<BattleMove*> moveset1 = { punchMove, healMove };
		std::vector<BattleMove*> moveset2 = { kickMove, shadowBoltMove };
		std::vector<BattleMove*> moveset3 = { slashMove, kickMove, healMove };

		std::unordered_map<Character::StatType, int> stats1
		{
			{Character::CUR_HP, 100},
			{Character::MAX_HP, 100},
			{Character::DEF, 2},
			{Character::ATK, 3},
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
		std::unordered_map<Character::StatType, int> stats3
		{
			{Character::CUR_HP, 500},
			{Character::MAX_HP, 500},
			{Character::DEF, 2},
			{Character::ATK, 5},
			{Character::HEAL, 2}
		};

		return std::vector<Character*>{
			new Character("Anduin", moveset1, stats1), 
			new Character("Gul'dan", moveset2, stats2),
			new Character("The Lich King", moveset3, stats3)
		};
	}
};