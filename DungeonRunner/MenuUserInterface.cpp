#include "MenuUserInterface.h"

MenuUserInterface::MenuUserInterface(InputReader* inputReader)
	: UserInterface(30, 1), inputReader(inputReader)
{
	inputReader->getOnInputRequestedEvent().addListener(this);
}

MenuUserInterface::~MenuUserInterface()
{
	inputReader->getOnInputRequestedEvent().removeListener(this);
}

void MenuUserInterface::onNotify(InputEventData eventData)
{
	displayLines.clear();
	for (int i = 0; i < eventData.optionDesciptions.size(); i++)
	{
		displayLines.push_back(DisplayLine(std::to_string(i) + " - " + eventData.optionDesciptions[i], LEFT));
	}
}

