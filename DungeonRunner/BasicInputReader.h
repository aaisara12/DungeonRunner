#pragma once
#include "InputReader.h"
class BasicInputReader : public InputReader
{
protected:
	virtual uint8_t getInput(std::string query, std::vector<std::string> optionDescriptions) override;
};