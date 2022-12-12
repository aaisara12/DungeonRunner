#include "GameManager.h"
#include "CharacterLoader.h"
#include "DummyCharacterLoader.h"

int main()
{
	// Get Characters
	CharacterLoader* characterLoader = new DummyCharacterLoader();

	// Do something
	GameManager game(characterLoader->getCharacters());

	game.start();
}