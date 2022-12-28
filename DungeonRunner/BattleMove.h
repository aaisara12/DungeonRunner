#pragma once
struct BattleMove
{
	// DESIGN CHOICE: Separate damage and heal fields to
	// make effect of move more clear instead of using the
	// indirect and error-prone method of simply checking
	// the sign of a single "health delta" field
	int damage;
	int heal;
	float accuracy;		// Range 0 - 1
	int cost;

	// This text can have formatting symbols like [s] and [t]
	// to represent where to insert the source and target names
	// into the action.
	std::string actionText;

	BattleMove(int damage, int heal, float accuracy, int cost, std::string actionText)
		:damage(damage), heal(heal), accuracy(accuracy), cost(cost), actionText(actionText)
	{}
};