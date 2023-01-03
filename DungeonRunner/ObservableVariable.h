#pragma once
#include "Event.h"
// A wrapper around a data field that has an
// event attached to it to broadcast to 
// any listeners about changes made to it.
// This makes it simple for the owner of the
// variable to invoke events when they change it

template <typename T>
class ObservableVariable
{
public:
	inline T get() { return value; }
	inline void set(T newValue) 
	{ 
		value = newValue; 
		onVariableChangedEvent.Invoke(value);
	}
	inline Event<T>& getOnVariableChangedEvent() { return onVariableChangedEvent; }

private:
	T value;
	Event<T> onVariableChangedEvent;
};