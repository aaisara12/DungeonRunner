#pragma once
#include "Process.h"
#include "InputReader.h"
#include "GameManager.h"
class MenuProcess : public Process
{
public:
	MenuProcess(InputReader* inputReader, GameManager& gameManager);

	// Inherited via Process
	virtual void tick(float deltaTime) override;
	virtual bool isFinished() const override;

private:
	InputReader* inputReader;
	GameManager& gameManager;	// For adding the selected process to the game (such as battle)
	bool _isFinished;
};