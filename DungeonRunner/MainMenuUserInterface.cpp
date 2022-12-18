#include "MainMenuUserInterface.h"

MainMenuUserInterface::MainMenuUserInterface( std::string title)
    :UserInterface(100, 1)
{
    currentDisplay.push_back(DisplayLine(title, LEFT));
}

const std::vector<UserInterface::DisplayLine>& MainMenuUserInterface::display()
{
    return currentDisplay;
}
