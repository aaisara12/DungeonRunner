#include "MenuUserInterface.h"

inline MenuUserInterface::MenuUserInterface(InputReader& inputReader)
	: UserInterface(30, 1), inputReader(inputReader)
{
	inputReader.getOnInputRequestedEvent().addListener(this);
}

MenuUserInterface::~MenuUserInterface()
{
	inputReader.getOnInputRequestedEvent().removeListener(this);
}

