#pragma once
#include <string>
#include "Observer.h"

class UserInterface
{
public:
	enum ContentAlignmentType
	{
		LEFT,
		RIGHT,
		CENTER
	};

	UserInterface(int frameWidthInCharacters, int frameHeightInCharacters, ContentAlignmentType alignment);

	// Returns a framed visual representation of the UI
	std::string getDisplay();


protected:
	// Returns a visual representation of the UI
	virtual std::string display() = 0;
};

