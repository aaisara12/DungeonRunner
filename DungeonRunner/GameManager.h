#pragma once
#include<list>
#include"Character.h"
class GameManager
{
public:
	GameManager(std::list<Character*> characters);

	// Start the game
	void start();

private:
	std::list<Character*> characters;
};