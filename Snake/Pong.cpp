#include "GameController.h"
#include "Graphics.h"
#include "Pong.h"

void Pong::Load()
{
	towardsWall = false;
	ballVelocity = -1;
	playerX = 10;
	playerY = 10;
	botX = 790;
	botY = 10;
	ballX = 500;
	ballY = 500;
	botSpeed = 5;
}
void Pong::Unload()
{
}

void Pong::Update(double timeDelta)
{
	if (playerY < 0)
		++playerY;

	else if (playerY > 600 - 75)
		--playerY;

	float tmpballX = (towardsWall * timeDelta * 100) - (!towardsWall * timeDelta * 100);
	float tmpballY = tmpballX * ballVelocity;


	if (ballX + tmpballX <= 20 || ballX + tmpballX >= 785)
	{

		if (Xcollision(ballX + tmpballX, ballY + tmpballY))
		{
			ballVelocity = -1 / ballVelocity;
			towardsWall = !towardsWall;
		}
	}


	if (ballY + tmpballY < 5 || ballY + tmpballY > 590)
	{
		ballVelocity = -1 / ballVelocity;
	}
	else
	{
		ballX += tmpballX;
		ballY += tmpballY;
	}

	if (ballY > botY + 37.5)
	{
		botY += botSpeed;
	}
	if (ballY < botY + 37.5)
	{
		botY -= botSpeed;
	}

	if (botSpeed > 1)
		botSpeed = botSpeed * 0.9999;
}

boolean Pong::Xcollision(float tmpballX, float tmpballY)
{
	if (tmpballY > playerY && ballY < playerY + 75)
		return true;
	if (ballX + tmpballX >= 780 && tmpballY > botY && ballY < botY + 75)
		return true;
	return false;
}

void Pong::Update(double timeDelta, WPARAM wParam)
{
	switch (wParam)
	{
	case VK_UP:
			playerY -= 5;
		break;
	case VK_DOWN:
			playerY += 5;
		break;
	default:
		break;
	}

	Update(timeDelta);
}

void Pong::Render()
{
	gfx->ClearScreen(0.0f, 0.0f, 0.0f);

	for (unsigned int ypos = 0; ypos < 600; ypos = ypos + 15)
	{
		gfx->FillRect(399, ypos, 2, 10, 1.0f, 1.0f, 1.0f, 1.0f);

	}

	gfx->FillRect(playerX, playerY, 5, 75, 1.0f, 1.0f, 1.0f, 1.0f);
	gfx->FillRect(botX, botY, 5, 75, 1.0f, 1.0f, 1.0f, 1.0f);

	gfx->FillCircle(ballX, ballY, 5, 1.0f, 1.0f, 1.0f, 1.0f);
}
