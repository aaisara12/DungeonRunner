#pragma once
#include<string>
#include<iostream>
#include<vector>
#include "Event.h"

struct InputEventData
{
	std::string query;
	std::vector<std::string> optionDesciptions;
	InputEventData(std::string query, std::vector<std::string> optionDesciptions)
		: query(query), optionDesciptions(optionDesciptions)
	{}
};

class InputReader
{
public:

	// DESIGN CHOICE: Wrapper around unique input implementation to ensure event is invoked.
	// Could have simply left it up to derived class to invoke, but this seemed prone to error.
	inline uint8_t requestInput(std::string query, std::vector<std::string> optionDescriptions)
	{
		onInputRequestedEvent.Invoke(InputEventData(query, optionDescriptions));
		return getInput(query, optionDescriptions);
	}

	inline Event<InputEventData>& getOnInputRequestedEvent() { return onInputRequestedEvent; }

protected:
	virtual uint8_t getInput(std::string query, std::vector<std::string> optionDescriptions) = 0;

private:
	Event<InputEventData> onInputRequestedEvent;
};