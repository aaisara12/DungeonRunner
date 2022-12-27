#pragma once
#include "BattleMove.h"
#include <list>

class Character;
struct BattleInteraction
{
	BattleMove* move;
	Character* source;
	Character* target;
};