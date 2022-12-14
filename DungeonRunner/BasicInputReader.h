#pragma once
#include "InputReader.h"
class BasicInputReader : public InputReader
{
public:
	virtual char getInput(std::string query, std::string inputOptions);
};