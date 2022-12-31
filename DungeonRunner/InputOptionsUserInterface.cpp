#include "InputOptionsUserInterface.h"

void InputOptionsUserInterface::setMenuOptions(std::vector<std::string>& optionDescriptions)
{
	displayLines.clear();
	for (int i = 0; i < optionDescriptions.size(); i++)
	{
		displayLines.push_back(DisplayLine(std::to_string(i) + " - " + optionDescriptions[i], LEFT));
	}
}

