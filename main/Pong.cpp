#include "GameController.h"
#include "Graphics.h"
#include "Pong.h"

void Pong::Load()
{
	towardsWall = true;
	ballVelocity = -1;
	playerX = 10;
	playerY = 10;
	botX = 790;
	botY = 10;
	ballX = 500;
	ballY = 500;
	botSpeed = 2;
	ballSpeed = 100;
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

	float tmpballX = (towardsWall * timeDelta * ballSpeed) - (!towardsWall * timeDelta * ballSpeed);
	float tmpballY = tmpballX * ballVelocity;



	if (Xcollision(ballX + tmpballX, ballY + tmpballY)) //Took a hour to find that I passed the sum of the delta AND the coords
	{
		ballVelocity = -1 / ballVelocity;
		towardsWall = !towardsWall;
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

	if (ballY > botY + 50 && botY + 75 < 600)
	{
		botY += botSpeed;
	}
	if (ballY < botY + 25 && botY > 0)
	{
		botY -= botSpeed;
	}

	ballSpeed = ballSpeed * 1.0001;
	botSpeed = botSpeed + 0.0001;

}

boolean Pong::Xcollision(float tmpballX, float tmpballY)
{
	if (tmpballX <= 17.5 && tmpballX >= 0 && tmpballY > playerY &&tmpballY < playerY + 75)
		return true;

	if (tmpballX >= 785 && tmpballX <= 800 && tmpballY > botY && tmpballY < botY + 75)
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

	gfx->renderCharacters(100, 100, 1.0f, 1.0f, 1.0f, 1.0f, L"Hello World", 1);

	gfx->FillCircle(ballX, ballY, 5, 1.0f, 1.0f, 1.0f, 1.0f);
}
