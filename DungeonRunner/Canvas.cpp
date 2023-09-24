#include "Canvas.h"
#include <iostream>
#include <Windows.h>

void Canvas::loadUserInterface(UserInterface* userInterface)
{
	userInterfaces.push_back(userInterface);
	userInterface->getOnDirtyEvent().addListener(this);
}

void Canvas::clearUserInterfaces()
{
	for (UserInterface* ui : userInterfaces)
	{
		ui->getOnDirtyEvent().removeListener(this);
	}
	userInterfaces.clear();
}

void Canvas::refreshDisplay()
{
	// DESIGN CHOICE: For now, just do costly step of refreshing all UI for sake of simplicity
	clearScreen();
	for (UserInterface* ui : userInterfaces)
	{
		std::cout << ui->getDisplay() << std::endl;
	}
}

void Canvas::onNotify(UserInterface* dirtyUserInterface)
{
	refreshDisplay();
}

#if defined(_WIN32)
#define PLATFORM_NAME "windows" // Windows
#elif defined(_WIN64)
#define PLATFORM_NAME "windows" // Windows
#endif
void Canvas::clearScreen(char fill) {
	if (PLATFORM_NAME == "windows")
	{
		// This is a little function from:
		// https://stackoverflow.com/questions/5866529/how-do-we-clear-the-console-in-assembly/5866648#5866648

		COORD tl = { 0,0 };
		CONSOLE_SCREEN_BUFFER_INFO s;
		HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
		GetConsoleScreenBufferInfo(console, &s);
		DWORD written, cells = s.dwSize.X * s.dwSize.Y;
		FillConsoleOutputCharacter(console, fill, cells, tl, &written);
		FillConsoleOutputAttribute(console, s.wAttributes, cells, tl, &written);
		SetConsoleCursorPosition(console, tl);
	}
}
