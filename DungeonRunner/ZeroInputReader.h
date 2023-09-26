#pragma once
#include "InputReader.h"

/// <summary>
/// A simple dummy input reader implementation that always submits the '0' character.
/// Used for testing or really dumb AI.
/// </summary>
class ZeroInputReader : public InputReader
{
	// Inherited via InputReader
	virtual char requestInput(std::string query) override
	{
		return '0';
	}
};