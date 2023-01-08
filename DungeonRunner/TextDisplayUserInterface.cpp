#include "TextDisplayUserInterface.h"

TextDisplayUserInterface::TextDisplayUserInterface(Event<std::string>& onTextChangedEvent)
	: UserInterface(30, 1), onTextChangedEvent(onTextChangedEvent)
{
	onTextChangedEvent.addListener(this);
}

TextDisplayUserInterface::~TextDisplayUserInterface()
{
	onTextChangedEvent.removeListener(this);
}

void TextDisplayUserInterface::onNotify(std::string eventData)
{
	getDisplayLines().clear();
	getDisplayLines().push_back(DisplayLine(eventData, LEFT));
}
