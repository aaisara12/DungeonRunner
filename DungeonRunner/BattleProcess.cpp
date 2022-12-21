#include "BattleProcess.h"

BattleProcess::BattleProcess(Character* boss, InputReader* inputReader)
    :boss(boss), inputReader(inputReader)
{
}

void BattleProcess::tick(float deltaTime)
{
}

bool BattleProcess::isFinished() const
{
    return false;
}
