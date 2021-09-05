#pragma once

#include "GameLevel.h"

class Level1 : public GameLevel
{
	float xPosition;

	SpriteSheet* sprites;

	int frame;

public:
	void Load() override;
	void Unload() override;
	void Render() override;
	void Update(double timeTotal, double timeDelta) override;
};