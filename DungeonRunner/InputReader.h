#pragma once
#include<string>
#include<iostream>
#include<vector>

class InputReader
{
public:
	// DESIGN CHOICE: InputReader only returns a char and needs not
	// care about what it means in any context (as opposed to being
	// coupled to the menu logic and returning the index of the proposed
	// options). This gives it greater flexibility and reduces coupling.

	virtual char requestInput(std::string query) = 0;

};