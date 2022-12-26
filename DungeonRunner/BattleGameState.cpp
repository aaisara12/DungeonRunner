#include "BattleGameState.h"


// DESIGN CHOICE: Dependency injection -- inject InputReader object
// into battle process so that onus is on external scripts to
// ensure a proper input reading module; this module does not have
// to test input creation and can assume it works for its own tests.
// This way, input creation logic does not need to clutter this process's code.

BattleGameState::BattleGameState(std::list<Character*> characters, Character* boss, InputReader* inputReader)
    : inputReader(inputReader), _isFinished(false)
{
    battleSystem = new BattleSystem(characters, boss); 
}

BattleGameState::~BattleGameState()
{
    delete battleSystem;
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
            queuedBattleCommands.pop_front();
            command->Execute(battleSystem);

        }
    }
    else
        _isFinished = true;     // Nothing left to do
}

