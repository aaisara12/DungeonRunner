#pragma once
#include "InputReader.h"
class BasicInputReader : public InputReader
{
public:
	virtual uint8_t requestInput(std::string query, std::vector<std::string> optionDescriptions) override;
};