#pragma once
#include <functional>
#include "Observer.h"

template <typename OwnerClass, typename EventData>
class Subscriber : Observer<EventData>
{
public:
	Subscriber(OwnerClass& owner, std::function<void(OwnerClass&, EventData)> callback)
		:owner(owner), callback(callback)
	{}

	virtual void onNotify(EventData eventData) override
	{
		callback(owner, eventData);
	}

private:
	const OwnerClass& owner;
	std::function<void(OwnerClass&, EventData)> callback;
};