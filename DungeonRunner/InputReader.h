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
	// DESIGN CHOICE: Split InputReader into two parts: a request and a resolution. 
	// A request represents defining the parameters for the input query, and
	// a resolution represents actually pausing the thread to try to acquire input
	// from the user. This split was made to enable greater control over input, as
	// it can cause the program to pause in undefined/unwanted places.

	virtual uint8_t requestInput(std::string query, std::vector<std::string> optionDescriptions) = 0;

};