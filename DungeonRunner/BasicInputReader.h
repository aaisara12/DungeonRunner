#pragma once
#include "InputReader.h"
class BasicInputReader : public InputReader
{
public:
	virtual char requestInput(std::string query) override;
};