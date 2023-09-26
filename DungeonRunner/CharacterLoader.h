#pragma once
#include<list>
#include"Character.h"
class CharacterLoader
{
public:
	virtual std::vector<Character*> getCharacters() = 0;
};