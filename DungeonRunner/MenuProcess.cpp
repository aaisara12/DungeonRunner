#include "MenuProcess.h"

MenuProcess::MenuProcess(InputReader* inputReader, GameManager& gameManager)
    :inputReader(inputReader), gameManager(gameManager), _isFinished(false)
{
}

void MenuProcess::tick(float deltaTime)
{
    char response = inputReader->getInput("What would you like to do?", "pq");
	switch (response)
	{
	case 'p':
		break;	// TODO
	case 'q':
		_isFinished = true;
	default:
		break;
	}
}

bool MenuProcess::isFinished() const
{
	return _isFinished;
}
