#pragma once
struct BattleMove
{
	// DESIGN CHOICE: Separate damage and heal fields to
	// make effect of move more clear instead of using the
	// indirect and error-prone method of simply checking
	// the sign of a single "health delta" field
	std::string name;
	int damage;
	int heal;
	float accuracy;		// Range 0 - 1
	int cost;

	enum TargetGroup 
	{
		ALLY,			// Any ally, including yourself
		ALLY_OTHER,		// Any ally, excluding yourself
		ALLY_ALL,		// All allies (AoE)
		ENEMY,			// Any enemy
		ENEMY_ALL		// All enemies (AoE)
	};

	TargetGroup targetGroup;

	// This text can have formatting symbols like [s] and [t]
	// to represent where to insert the source and target names
	// into the action.
	std::string actionText;

	BattleMove(std::string name, int damage, int heal, float accuracy, int cost, std::string actionText, TargetGroup targetGroup)
		:name(name), damage(damage), heal(heal), accuracy(accuracy), cost(cost), actionText(actionText), targetGroup(targetGroup)
	{}

	inline std::string getName() const { return name; }
};