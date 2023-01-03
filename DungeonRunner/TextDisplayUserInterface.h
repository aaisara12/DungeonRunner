#pragma once
#include "UserInterface.h"
#include "Observer.h"
#include "ObservableVariable.h"
#include <string>

class TextDisplayUserInterface : public UserInterface, Observer<std::string>
{
public:
	TextDisplayUserInterface(Event<std::string>& onTextChangedEvent);
	virtual ~TextDisplayUserInterface() override;

private:
	Event<std::string>& onTextChangedEvent;

	// Inherited via Observer
	virtual void onNotify(std::string eventData);
};