#pragma once

// An observer can be thought of as a sort of "wrapper" around a
// callback implementation; the broadcaster of the event deals in
// terms of observers and can invoke these callbacks with the proper
// information since the Observer class has a defined onNotify method.
template <typename EventData>
class Observer
{
public:
	// We want this here since it will be inherited from, and we want 
	// the derived class's destructors to be called
	virtual ~Observer(){}

	virtual void onNotify(EventData eventData) = 0;
};