#include "BattleGameState.h"
#include "BattleMove.h"
#include "ApplyBattleInteractionCommand.h"
#include "DescribeBattleInteractionCommand.h"
#include "ClearBattleInteractionCommand.h"
#include "ChangeTextCommand.h"
#include "EvaluateBattleStateCommand.h"
#include "EndBattleCommand.h"

// DESIGN CHOICE: Dependency injection -- inject InputReader object
// into battle process so that onus is on external scripts to
// ensure a proper input reading module; this module does not have
// to test input creation and can assume it works for its own tests.
// This way, input creation logic does not need to clutter this process's code.

BattleGameState::BattleGameState(std::vector<Character*> characters, Character* boss, OptionSelector* optionSelector)
    : optionSelector(optionSelector), characters(characters), boss(boss), _isFinished(false)
{}

void BattleGameState::tick(float deltaTime)
{
    if (queuedBattleCommands.empty())
        initializeCharacterActions();
    else
    {
        queuedBattleCommands.front().timeRemaining -= deltaTime;
        if (queuedBattleCommands.front().timeRemaining <= 0)
        {
            // Pop command before execution so that command can
            // add more commands to the front of the queue easily
            Command* command = queuedBattleCommands.front().command;
            queuedBattleCommands.pop_front();
            std::list<Command*> generatedCommands = command->Execute(currentBattleText);

            // Push all generated commands onto command queue (it's recursive, so go straight to the front)
            // with delay that scales based on time it takes to read the current text
            for (Command* command : generatedCommands)
            {
                // TODO: Link this up with the actual display speed of the UI?
                const float estimatedReadingSpeedCharsPerSecond = 10;
                queuedBattleCommands.push_front(DelayedCommand(currentBattleText.get().size() / estimatedReadingSpeedCharsPerSecond, command));
            }

            delete command;
        }
    }
}

void BattleGameState::evaluateBattleState()
{
    // If party has been completely defeated, then queue DEFEAT commands at front of queue (defeat msg, end game)
    // NOTE: Queueing at front ensures that any previous victory condition (boss being defeated) is 
    // overridden by this defeat condition, which is necessary if, for example, the boss has a self-destruct move
    // that deals damage to everyone and defeats everyone in the party
    // Else if boss has been defeated, then queue VICTORY commands at end of queue (victory msg, xp check, end game) 

    bool isPartyDefeated = true;
    for (Character* character : characters)
    {
        if (character->getStats()[Character::StatType::CUR_HP] > 0)
            isPartyDefeated = false;
    }

    bool isEnemyDefeated = boss->getStats()[Character::StatType::CUR_HP] <= 0;


    // Check either of the two end game conditions
    if (isPartyDefeated)
    {
        queuedBattleCommands.clear();
        queuedBattleCommands.push_back(DelayedCommand(0, new ChangeTextCommand("Your party has been defeated.")));
        queuedBattleCommands.push_back(DelayedCommand(2, new EndBattleCommand(this)));
    }
    else if (isEnemyDefeated)
    {
        queuedBattleCommands.clear();
        queuedBattleCommands.push_back(DelayedCommand(2, new ChangeTextCommand("Victory!")));
        queuedBattleCommands.push_back(DelayedCommand(2, new EndBattleCommand(this)));

    }
}

void BattleGameState::endBattle()
{
    _isFinished = true;
}

void BattleGameState::initializeCharacterActions()
{
    for (Character* character : characters)
    {
        // Query for the move of this character 
        BattleMove* selectedMove = optionSelector->queryOptions("Move Selection", character->getMoves());

        // TODO: Curate characters to choose from based on selected move (heal, AOE, single target, etc.)
        std::vector<Character*> validTargets = characters;

        Character* selectedTarget = optionSelector->queryOptions("Target Selection", validTargets);

        // TODO: queue up a command based on this input
        BattleInteraction interaction;
        interaction.move = selectedMove;
        interaction.source = character;
        interaction.target = selectedTarget;

        queuedBattleCommands.push_back(DelayedCommand(0.0f, new DescribeBattleInteractionCommand(interaction)));
        queuedBattleCommands.push_back(DelayedCommand(2.0f, new ApplyBattleInteractionCommand(interaction, this)));
        queuedBattleCommands.push_back(DelayedCommand(2.0f, new ClearBattleInteractionCommand()));
    }
}

