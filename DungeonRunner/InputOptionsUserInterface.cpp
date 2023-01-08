#include "InputOptionsUserInterface.h"

void InputOptionsUserInterface::setMenuOptions(std::vector<std::string>& optionDescriptions)
{
	getDisplayLines().clear();
	for (int i = 0; i < optionDescriptions.size(); i++)
	{
		getDisplayLines().push_back(DisplayLine(std::to_string(i) + " - " + optionDescriptions[i], LEFT));
	}
}

