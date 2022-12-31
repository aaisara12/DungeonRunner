#include "BasicInputReader.h"

uint8_t BasicInputReader::requestInput(std::string query, std::vector<std::string> optionDescriptions)
{
	int ans;
	std::cout << (query + ": ");
	std::cin >> ans;

	// TODO: Add some form of validation to make sure
	// invalid input is handled in a defined way
	// (Right now, can't be sure a valid digit was entered)
	return ans;
}
