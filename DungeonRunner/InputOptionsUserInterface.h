#pragma once
#include "UserInterface.h"
#include "Observer.h"
#include "InputReader.h"

class InputOptionsUserInterface : public UserInterface
{
public:
	InputOptionsUserInterface()
		: UserInterface(30, 1)
	{}

	void setMenuOptions(std::vector<std::string>& optionDescriptions);

};