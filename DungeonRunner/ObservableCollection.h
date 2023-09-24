#pragma once
#include "Event.h"

/// <summary>
/// See ObservableVariable. Same idea but for a collection.
/// </summary>
/// <typeparam name="T"></typeparam>
/// <typeparam name="CollectionOfT"></typeparam>
template <typename CollectionOfT>
class ObservableCollection
{
public:
	inline void push_back(typename CollectionOfT::value_type item)
	{
		collection.push_back(item);
		onCollectionChanged.Invoke(collection);
	}

	inline void clear()
	{
		collection.clear();
		onCollectionChanged.Invoke(collection);
	}

	inline Event<const CollectionOfT&>& getOnCollectionChangedEvent()
	{
		return onCollectionChanged;
	}

	inline const CollectionOfT get()
	{
		return collection;
	}

private:
	CollectionOfT collection;
	Event<const CollectionOfT&> onCollectionChanged;
};