#include "Character.h"

Character::Character(std::string name)
	:name(name), voiceLines({})
{
	stats = std::unordered_map<StatType, int>
	{
		{StatType::MAX_HP, 10},
		{StatType::CUR_HP, 10},
		{StatType::ATK, 1},
		{StatType::DEF, 0}
	};
}

Character::Character(std::string name, std::unordered_map<StatType, int> stats, std::list<std::string> voiceLines)
	:name(name), voiceLines(voiceLines)
{
	this->stats = std::unordered_map<StatType, int>
	{
		{StatType::MAX_HP, stats.count(StatType::MAX_HP) != 0? stats[StatType::MAX_HP] : 0},
		{StatType::CUR_HP, stats.count(StatType::CUR_HP) != 0 ? stats[StatType::CUR_HP] : 0},
		{StatType::ATK, stats.count(StatType::ATK) != 0 ? stats[StatType::ATK] : 0},
		{StatType::DEF, stats.count(StatType::DEF) != 0 ? stats[StatType::DEF] : 0}
	};
}

void Character::takeDamage(int dmg)
{
	// TODO
}