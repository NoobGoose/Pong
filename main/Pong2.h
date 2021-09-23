#pragma once

#include "GameLevel.h"

class Pong2 : public GameLevel
{
	bool towardsWall;
	float ballVelocity;
	float playerX, playerY;
	float botX, botY;
	float botSpeed;
	float ballSpeed;
	float ballX, ballY;

	unsigned int player1Score;
	unsigned int player2Score;

public:

	void Load() override;
	void Unload() override;
	void Render() override;
	void Update(double timeDelta) override;
	void Update(double timeDelta, WPARAM wParam) override;

	boolean Xcollision(float tmpballX, float tmpballY);

};
