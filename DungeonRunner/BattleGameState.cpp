#include "BattleGameState.h"
#include "BattleMove.h"
#include "ApplyBattleInteractionCommand.h"
#include "DescribeBattleInteractionCommand.h"
#include "ClearBattleInteractionCommand.h"
#include "ChangeTextCommand.h"
#include "EvaluateBattleStateCommand.h"
#include "EndBattleCommand.h"
#include <format>

// DESIGN CHOICE: Dependency injection -- inject InputReader object
// into battle process so that onus is on external scripts to
// ensure a proper input reading module; this module does not have
// to test input creation and can assume it works for its own tests.
// This way, input creation logic does not need to clutter this process's code.

BattleGameState::BattleGameState(std::vector<Character*> partyA, std::vector<Character*> partyB, InputReader* userInput, InputReader* aiInput, OptionSelector* optionSelector)
    : optionSelector(optionSelector), _isFinished(false)
{

    // userInput and aiInput are not coupled with party A or B necessarily, which allows for user and CPU-controlled
    // characters in both parties
   
    // User-controlled ally characters
    for (auto character : partyA)
    {
        // In current implementation, all characters in Party A are user-controlled
        battlingCharacters.emplace_back(character, Team::ALLY, userInput);
    }

    // CPU-controlled enemy characters
    for (auto character : partyB)
    {
        battlingCharacters.emplace_back(character, Team::ENEMY, aiInput);
    }

    // Perhaps in a future implementation, there could be a Party C which contains CPU-controlled ally characters

}

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

            // Add delays to all of the commands
            std::list<DelayedCommand> generatedDelayedCommands;
            for (Command* generatedCommand : generatedCommands)
            {
                // DESIGN CHOICE: Use a fixed delay of 2 seconds for simplicity instead of scaling
                // with how much text there is to read. This will help reduce variables while debugging
                // at least until the entire project is stabilized.
                generatedDelayedCommands.push_back(DelayedCommand(2.0f, generatedCommand));
            }

            // Push all generated commands onto command queue (commands are resolved LIFO, so push at front of queue)
            queuedBattleCommands.insert(queuedBattleCommands.begin(), generatedDelayedCommands.begin(), generatedDelayedCommands.end());

            delete command;
        }
    }
}

void BattleGameState::onEnter()
{
    // Check the current game state. This prevents a battle from occurring
    // if the enemy / party have already been defeated ( HP == 0)
    evaluateBattleState();
}

void BattleGameState::onExit()
{
    currentBattleText.set("");
    queuedBattleCommands.clear();
    _isFinished = false;
}

void BattleGameState::evaluateBattleState()
{
    // If party has been completely defeated, then queue DEFEAT commands at front of queue (defeat msg, end game)
    // NOTE: Queueing at front ensures that any previous victory condition (boss being defeated) is 
    // overridden by this defeat condition, which is necessary if, for example, the boss has a self-destruct move
    // that deals damage to everyone and defeats everyone in the party
    // Else if boss has been defeated, then queue VICTORY commands at end of queue (victory msg, xp check, end game) 

    bool isPartyDefeated = true;
    bool isEnemyDefeated = true;

    for (const auto& battlingCharacter : battlingCharacters)
    {
        if (battlingCharacter.character->getStats()[Character::StatType::CUR_HP] > 0)
        {
            if (battlingCharacter.team == Team::ALLY)
                isPartyDefeated = false;
            if (battlingCharacter.team == Team::ENEMY)
                isEnemyDefeated = false;
        }

    }


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
        queuedBattleCommands.push_back(DelayedCommand(0, new ChangeTextCommand("Victory!")));
        queuedBattleCommands.push_back(DelayedCommand(2, new EndBattleCommand(this)));

    }
}

void BattleGameState::endBattle()
{
    _isFinished = true;
}

void BattleGameState::initializeCharacterActions()
{
    for (const auto& battlingCharacter : battlingCharacters)
    {
        Character* character = battlingCharacter.character;
        InputReader* inputReader = battlingCharacter.inputReader;

        // Query for the move of this character 
        std::string moveSelectionPrompt = std::format("What should {} do?", character->getName());
        currentBattleText.set(moveSelectionPrompt);
        BattleMove* selectedMove = optionSelector->queryOptions(inputReader, "Move Selection", character->getMoves());

        // TODO: Curate characters to choose from based on selected move (heal, AOE, single target, etc.)

        std::string targetSelectionPrompt = std::format("Who should {} target?", character->getName());
        currentBattleText.set(targetSelectionPrompt);
        std::vector<Character*> validTargets = getTargetCharacters(battlingCharacter, selectedMove->targetGroup);

        Character* selectedTarget = optionSelector->queryOptions(inputReader, "Target Selection", validTargets);

        BattleInteraction interaction;
        interaction.move = selectedMove;
        interaction.source = character;
        interaction.target = selectedTarget;

        queuedBattleCommands.push_back(DelayedCommand(0.0f, new DescribeBattleInteractionCommand(interaction)));
        queuedBattleCommands.push_back(DelayedCommand(2.0f, new ApplyBattleInteractionCommand(interaction, this)));
        //queuedBattleCommands.push_back(DelayedCommand(2.0f, new ClearBattleInteractionCommand()));
    }
}

std::vector<Character*> BattleGameState::getTargetCharacters(BattleCharacter sourceCharacter, BattleMove::TargetGroup targetGroup)
{
    // TODO: Implement!
    std::vector<Character*> targets;

    // DESIGN CHOICE: Default conditions evaluate to false so that unimplemented target groups
    // by default don't result in any targets, which makes it easier to detect the error
    std::function<bool(Team, Team)> teamCondition = [](Team a, Team b) {return false; };
    std::function<bool(Character*, Character*)> characterCondition = [](Character* a, Character* b) {return false; };

    // DESIGN CHOICE: Modify conditions for adding characters instead of performing logic.
    // While it requires extra variables, it makes the code easier to understand and reduces
    // repetitions
    switch (targetGroup)
    {
    case BattleMove::ALLY:
        teamCondition = [](Team target, Team source) {return target == source; };
        characterCondition = [](Character* target, Character* source) { return true; };
        break;
    case BattleMove::ALLY_OTHER:
        teamCondition = [](Team target, Team source) {return target == source; };
        characterCondition = [](Character* target, Character* source) { return target != source; };
        break;
    case BattleMove::ENEMY:
        teamCondition = [](Team target, Team source) {return target != source; };
        characterCondition = [](Character* target, Character* source) { return true; };
    default:
        break;
    }

    // Add characters to target list based on condition check
    for (const auto& battlingCharacter : battlingCharacters)
    {
        if (teamCondition(battlingCharacter.team, sourceCharacter.team) &&
            characterCondition(battlingCharacter.character, sourceCharacter.character))
            targets.push_back(battlingCharacter.character);
    }
 
    return targets;
}

