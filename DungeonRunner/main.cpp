#include "GameManager.h"
#include "CharacterLoader.h"
#include "DummyCharacterLoader.h"
#include "BasicInputReader.h"

int main()
{
	// Get Characters
	CharacterLoader* characterLoader = new DummyCharacterLoader();
	InputReader* inputReader = new BasicInputReader();

	// Do something
	GameManager game(characterLoader->getCharacters(), inputReader);

	game.start();

	delete characterLoader;
	delete inputReader;
}