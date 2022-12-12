#include "GameManager.h"
#include <iostream>

GameManager::GameManager(std::list<Character*> characters)
	: characters(characters)
{
}

void GameManager::start()
{
	std::cout << "Game start!" << std::endl;
}
