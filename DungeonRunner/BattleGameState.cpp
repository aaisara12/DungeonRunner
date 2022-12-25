#include "BattleGameState.h"

BattleGameState::BattleGameState(Character* boss, InputReader* inputReader)
    :boss(boss), inputReader(inputReader), _isFinished(false)
{
}

void BattleGameState::tick(float deltaTime)
{
    if (!queuedBattleCommands.empty())
    {
        queuedBattleCommands.front().timeRemaining -= deltaTime;
        if (queuedBattleCommands.front().timeRemaining <= 0)
        {

            // Pop command before execution so that command can
            // add more commands to the front of the queue easily
            Command* command = queuedBattleCommands.front().command;
            queuedBattleCommands.pop();
            command->Execute(queuedBattleCommands);

            // TODO: Implement logic for input request command
        }
    }
    else
        _isFinished = true;     // Nothing left to do
}

