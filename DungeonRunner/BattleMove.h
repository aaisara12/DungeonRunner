#pragma once
struct BattleMove
{
	int damage;
	float accuracy;		// Range 0 - 1
	int cost;

	// This text can have formatting symbols like [s] and [t]
	// to represent where to insert the source and target names
	// into the action.
	std::string actionText;

	BattleMove(int damage, float accuracy, int cost, std::string actionText)
		:damage(damage), accuracy(accuracy), cost(cost), actionText(actionText)
	{}
};