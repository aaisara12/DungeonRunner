#pragma once
#include "UserInterface.h"
#include "Observer.h"

/// <summary>
/// Represents the entire display the user sees in the terminal window.
/// </summary>
class Canvas : public Observer<UserInterface*>
{
public:

	/// <summary>
	/// Add a UserInterface to this Canvas
	/// </summary>
	/// <param name="userInterface"></param>
	void loadUserInterface(UserInterface* userInterface);

	/// <summary>
	/// Remove all UserInterfaces from this Canvas
	/// </summary>
	void clearUserInterfaces();

private:

	std::vector<UserInterface*> userInterfaces;

	/// <summary>
	/// Clear the terminal window and display the current UserInterfaces
	/// </summary>
	void refreshDisplay();

	void clearScreen(char fill = ' ');

	// Inherited via Observer
	virtual void onNotify(UserInterface* dirtyUserInterface);

};