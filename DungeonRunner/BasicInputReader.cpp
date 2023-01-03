#include "BasicInputReader.h"

char BasicInputReader::requestInput(std::string query)
{
	char ans;
	std::cout << (query + ": ");
	std::cin >> ans;

	return ans;
}
