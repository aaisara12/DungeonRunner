#include "GameManager.h"
#include "CharacterLoader.h"
#include "DummyCharacterLoader.h"
#include "BasicInputReader.h"
#include "ZeroInputReader.h"

int main()
{
	// Get Characters
	CharacterLoader* characterLoader = new DummyCharacterLoader();
	InputReader* playerInput = new BasicInputReader();
	InputReader* enemyInput = new ZeroInputReader();

	// Do something
	GameManager game(characterLoader->getCharacters(), playerInput, enemyInput);

	game.start();

	delete characterLoader;
	delete playerInput;
	delete enemyInput;
}