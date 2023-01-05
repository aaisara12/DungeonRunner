#include "EvaluateBattleStateCommand.h"
#include "BattleGameState.h"

std::list<Command*> EvaluateBattleStateCommand::Execute(ObservableVariable<std::string>& textOutput)
{
    battleGameState->evaluateBattleState();
    return std::list<Command*>();
}
