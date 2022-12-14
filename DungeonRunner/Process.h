#pragma once
#include "Event.h"
class Process
{
public:
	virtual void tick(float deltaTime) = 0;

	// Function for checking whether this process has finished.
	// We use this instead of an event broadcast because
	// pretty much only the GameManager cares about this, and
	// it's not worth the additional overhead of this pattern
	virtual bool isFinished() const = 0;
};