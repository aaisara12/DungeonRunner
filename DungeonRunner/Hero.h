#pragma once
#include "Character.h"

class Hero : Character
{
public:

	enum HeroStatType
	{
		MAX_XP,
		CUR_XP,
		LVL
	};

	Hero();
	virtual ~Hero();

	// Accessers
	inline const std::unordered_map<HeroStatType, int>& getHeroStats() const { return heroStats; }
	inline char getVisualRepresentation() const { return visualRepresentation; }

	// Modifiers
	void gainExperience(int amt);

private:
	char visualRepresentation;
	std::unordered_map<HeroStatType, int> heroStats;
};