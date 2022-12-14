#pragma once
#include<string>
#include<iostream>
class InputReader
{
public:
	virtual char getInput(std::string query, std::string inputOptions) = 0;
};
