#pragma once
#include "UserInterface.h"
#include "Character.h"


// While this does use multiple inheritence which can lead to
// the diamond problem, I don't foresee it occurring given that UserInterface and Observer
// aren't really intended to inherit from the same base class.
// It's not really worth the overhead to use the component pattern here, especially since we're
// only merging the functionality of two classes (instead of 10+ like for GameObjects in Unity)
class HealthBarUserInterface : public UserInterface, public Observer<ContainerUpdateEventData>
{
public:
	// Inherited via Observer (update display image)
	virtual void onNotify(float eventData);

protected:
	virtual std::string display();
};