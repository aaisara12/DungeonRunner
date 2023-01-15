#pragma once
#include "Event.h"
#include <string>
#include <vector>
#include "InputReader.h"
#include "InputOptionsUserInterface.h"

class OptionSelector
{
public:

	// DESIGN CHOICE: Inject user interface into options selector in case it needs to
	// be formatted in a particular way. For example, the GameManager should ensure
	// all user interfaces used in the game have the same dimensions.
	OptionSelector(InputOptionsUserInterface* userInterface)
		: userInterface(userInterface)
	{}

	// Query field is important for helping user distinguish what
	// kind of choice they're making (character move, target, etc.)
	template <typename T>
	T queryOptions(InputReader* inputReader, std::string query, const std::vector<T>& options);

	inline Event<bool>& getOnQueryCompletedEvent() { return onQueryCompleted; }

private:
	InputOptionsUserInterface* userInterface;

	// Event data type is bool as a filler since no actual data other than
	// the event being raised needs to be returned
	Event<bool> onQueryCompleted;
};


template<typename T>
inline T OptionSelector::queryOptions(InputReader* inputReader, std::string query, const std::vector<T>& options)
{
	// Special case where UI must be set up before its target activates
	// Requesting input pauses the thread, so we have to display the UI
	// before the theread is paused

	// TODO: Make UI display query instead of having the input reader do it for a cleaner look
	
	std::string me;
	
	std::vector<std::string> optionNames;
	for (const T& option : options)
	{
		optionNames.push_back(option->getName());
	}

	userInterface->setMenuOptions(optionNames);
	std::cout << userInterface->getDisplay() << std::endl;

	// Tightly coupled with InputOptionsUserInterface, which labels each
	// option with a number 0 - n
	int selectionIndex = inputReader->requestInput(query) - '0';

	onQueryCompleted.Invoke(true);

	return options[selectionIndex];
}