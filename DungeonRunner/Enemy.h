#pragma once
#include "Character.h"

class Enemy : Character
{
public:
	Enemy();
	virtual ~Enemy();

	// Accessers
	inline const VisualRepresentation3x3& getVisualRepresentation() const { return visualRepresentation; }

private:
	VisualRepresentation3x3 visualRepresentation;
};

// Simple way of passing 2D array
struct VisualRepresentation3x3
{
	char val[3][3];
};