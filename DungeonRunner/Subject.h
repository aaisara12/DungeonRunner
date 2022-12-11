#pragma once
#include<list>
#include "Observer.h"
template <typename EventData>
class Subject
{
public:
	void addObserver(Observer<EventData>* observer);
	void removeObserver(Observer<EventData>* observer);

protected:
	// Broadcast to all observers (iterate through all observers and notify)
	void Invoke();

private:
	// Use list instead of vector here since there probably won't be
	// a ton of observers per subject (making it fast to loop through
	// and locate an observer to remove), and we'll need to insert and
	// remove observers relatively frequently
	// 
	// Reminder on when to use vectors vs lists:
	// Vectors are great when we are given some sort of relatively stable
	// set of data in contiguous memory (such as an incoming data to fill out).
	// Being contiguous makes it easy to cast it into new structs and also
	// makes it simple to do random and specific access of a particular piece
	// of the data.
	// However, when it comes to inserting or removing elements, they don't
	// work as well because their iterators get invalidated (since data could
	// be deleted and copied elsewhere due to be resizeable). Additionally,
	// adding or removing elements is often more expensive since it involves
	// shifting over large amounts of data in a particular direction (if not
	// at the end).
	std::list<Observer<EventData*>*> observers;
};