#pragma once
#include "CharacterLoader.h"
class DummyCharacterLoader : public CharacterLoader
{
public:
	inline virtual std::list<Character*> getCharacters()
	{
		return std::list<Character*>{new Character("Anduin"), new Character("Gul'dan")};
	}
};