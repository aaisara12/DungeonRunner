#pragma once
#include<unordered_map>
#include<list>
#include<string>
#include "Event.h"
#include "BattleMove.h"
#include "BattleInteraction.h"

struct ContainerUpdateEventData;
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
	Character(std::string name, std::unordered_map<StatType, int> stats);
	virtual ~Character() {};	// Calls derived class destructors

	// Accessers
	inline const std::string getName() const { return name; }
	inline std::unordered_map<StatType, int> getStats() { return stats; }
	inline const std::vector<BattleMove*>& getMoves() const { return moves; }

	inline Event<ContainerUpdateEventData>& getHealthDataChangedEvent() { return healthDataChangedEvent; }


	// Modifiers

	// Apply the provided battle interaction to this character (source should be this character)
	// and return back any battle interactions it generates
	std::list<BattleInteraction> applyBattleInteraction(BattleInteraction battleInteraction);

private:
	std::string name;
	std::unordered_map<StatType, int> stats;


	// DESIGN CHOICE: Vector since I want characters to have variable number of moves.
	// Could have used a list, but might as well get faster access time with
	// resizeable array. List might only be better if we were constantly modifying
	// the movesets of the characters, but since they stay constant throughout the
	// entire game, we don't gain much from the flexibility of a list
	std::vector<BattleMove*> moves;
	
	// Event invoked when this character's health information is changed
	Event<ContainerUpdateEventData> healthDataChangedEvent;
};

// Data structure for holding information about an updated container-based value
// Container-based values are those that start at 0 and cap at some value
struct ContainerUpdateEventData
{
	int newContainerMax;
	int newContainerCurrent;

	ContainerUpdateEventData(int newContainerCurrent, int newContainerMax)
		: newContainerCurrent(newContainerCurrent), newContainerMax(newContainerMax)
	{}
};
