#include "MainMenuUserInterface.h"

MainMenuUserInterface::MainMenuUserInterface( std::string title)
    :UserInterface(50, 2)
{
    currentDisplay.push_back(DisplayLine(title, CENTER));
}

const std::vector<UserInterface::DisplayLine>& MainMenuUserInterface::display()
{
    return currentDisplay;
}
