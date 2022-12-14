#include "BasicInputReader.h"

char BasicInputReader::getInput(std::string query, std::string inputOptions)
{
	std::string inputOptionsFormatted = "[";
	for (char option : inputOptions)
	{
		inputOptionsFormatted.push_back(option);
		inputOptionsFormatted.push_back('|');
	}
	inputOptionsFormatted[inputOptionsFormatted.size() - 1] = ']';

	char ans;
	std::cout << (query + " " + inputOptionsFormatted + ": ");
	std::cin >> ans;

	return ans;
}
