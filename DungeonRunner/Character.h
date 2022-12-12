#pragma once
#include<unordered_map>
#include<list>
#include<string>
#include "Event.h"

// Data structure for holding information about an updated container-based value
// Container-based values are those that start at 0 and cap at some value
struct ContainerUpdateData
{
	uint32_t newContainerMax;
	uint32_t newContainerCurrent;
};



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

	Character(std::string name);
	Character(std::string name, std::unordered_map<StatType, int> stats, std::list<std::string> voiceLines);
	virtual ~Character() {};	// Calls derived class destructors

	// Accessers
	inline const std::unordered_map<StatType, int>& getStats() const { return stats; }
	inline Event<ContainerUpdateData>& getHealthDataChangedEvent() { return healthDataChangedEvent; }
	inline std::string getName() const { return name; }

	// Modifiers
	void takeDamage(int dmg);

private:
	std::unordered_map<StatType, int> stats;
	std::list<std::string> voiceLines;
	std::string name;
	
	// Event invoked when this character's health information is changed
	Event<ContainerUpdateData> healthDataChangedEvent;
};
