#pragma once
#include "UserInterface.h"
#include "Observer.h"
#include "InputReader.h"

class MenuUserInterface : public UserInterface, public Observer<InputEventData>
{
public:
	MenuUserInterface(InputReader& inputReader);
	virtual ~MenuUserInterface() override;

private:
	InputReader& inputReader;

};