#pragma once
#include<unordered_map>
#include<list>
#include<string>


class Character
{
public:
	enum StatType
	{
		MAX_HP,
		CUR_HP,
		ATK,
		DEF
	};

	Character();
	virtual ~Character();	// Calls derived class destructors

	// Accessers
	inline const std::unordered_map<StatType, int>& getStats() const { return stats; }
	inline std::string getName() const { return name; }

	// Modifiers;
	void takeDamage(int dmg);

private:
	std::unordered_map<StatType, int> stats;
	std::list<std::string> voiceLines;
	std::string name;
};
