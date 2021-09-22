#pragma once

#include "GameLevel.h"

class Snake : public GameLevel
{
	char fourValueBool;
	int playerX, playerY;
	int appleX, appleY;
	int matrix[30][40];

public:

	void Load() override;
	void Unload() override;
	void Render() override;
	void Update(double timeDelta) override;
	void Update(double timeDelta, WPARAM wParam) override;

};
