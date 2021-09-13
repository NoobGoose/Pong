#pragma once

#define _USE_MATH_DEFINES

#include "GameLevel.h"
#include <math.h>
#include <ctime>

class Pong : public GameLevel
{
	bool towardsWall;
	float ballVelocity;
	float playerX, playerY;
	float botX, botY;
	float botSpeed;
	float ballX, ballY;

public:

	void Load() override;
	void Unload() override;
	void Render() override;
	void Update(double timeDelta) override;
	void Update(double timeDelta, WPARAM wParam) override;

	boolean Xcollision(float tmpballX, float tmpballY);

};
