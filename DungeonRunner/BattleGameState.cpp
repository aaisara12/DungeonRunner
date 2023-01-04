#include "BattleGameState.h"
#include "BattleMove.h"
#include "ApplyBattleInteractionCommand.h"
#include "DescribeBattleInteractionCommand.h"
#include "ClearBattleInteractionCommand.h"

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
        queuedBattleCommands.push_back(DelayedCommand(2.0f, new ApplyBattleInteractionCommand(interaction)));
        queuedBattleCommands.push_back(DelayedCommand(2.0f, new ClearBattleInteractionCommand()));
    }
}

