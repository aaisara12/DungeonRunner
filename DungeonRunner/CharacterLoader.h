#pragma once
#include<list>
#include"Character.h"
class CharacterLoader
{
public:
	virtual std::list<Character*> getCharacters() = 0;
};