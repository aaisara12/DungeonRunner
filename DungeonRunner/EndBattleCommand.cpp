#include "EndBattleCommand.h"
#include "BattleGameState.h"

std::list<Command*> EndBattleCommand::Execute(ObservableVariable<std::string>& textOutput)
{
    battleGameState->endBattle();
    return std::list<Command*>();
}
