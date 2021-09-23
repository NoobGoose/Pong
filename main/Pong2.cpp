#include "GameController.h"
#include "Graphics.h"
#include "Pong2.h"

void Pong2::Load()
{
	towardsWall = true;
	ballVelocity = -1;
	playerX = 10;
	playerY = 10;
	botX = 790;
	botY = 10;
	ballX = 500;
	ballY = 500;
	ballSpeed = 100;

	player1Score = 0;
	player2Score = 0;
}
void Pong2::Unload()
{
}

void Pong2::Update(double timeDelta)
{
	if (playerY < 0)
		++playerY;

	else if (playerY > 600 - 75)
		--playerY;

	if (botY < 0)
		++botY;

	else if (botY > 600 - 75)
		--botY;

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

	ballSpeed = ballSpeed * 1.001;


	if (ballX < 0)
	{
		player2Score++;
		ballX = 600 + ((player2Score * 100) % 200);
		ballY = 500;
		ballSpeed = 100;
		botSpeed = 2;
	}

	if (ballX > 800)
	{
		player1Score++;
		ballX = 400 - ((player1Score * 100) % 200);
		ballY = 500;
		ballSpeed = 100;
	}
}

boolean Pong2::Xcollision(float tmpballX, float tmpballY)
{
	if (tmpballX <= 17.5 && tmpballX >= 0 && tmpballY > playerY && tmpballY < playerY + 75)
		return true;

	if (tmpballX >= 785 && tmpballX <= 800 && tmpballY > botY && tmpballY < botY + 75)
		return true;

	return false;
}

void Pong2::Update(double timeDelta, WPARAM wParam)
{
	switch (wParam)
	{
	case 0x57:
		playerY -= 10;
		break;
	case 0x53:
		playerY += 10;
		break;
	case VK_UP:
		botY -= 10;
		break;
	case VK_DOWN:
		botY += 10;
		break;
	default:
		break;
	}

	Update(timeDelta);
}

void Pong2::Render()
{
	gfx->ClearScreen(0.0f, 0.0f, 0.0f);

	for (unsigned int ypos = 0; ypos < 600; ypos = ypos + 15)
	{
		gfx->FillRect(399, ypos, 2, 10, 1.0f, 1.0f, 1.0f, 1.0f);

	}

	gfx->FillRect(playerX, playerY, 5, 75, 1.0f, 1.0f, 1.0f, 1.0f);
	gfx->FillRect(botX, botY, 5, 75, 1.0f, 1.0f, 1.0f, 1.0f);

	gfx->renderCharacters(318, 10, 1.0f, 1.0f, 1.0f, 1.0f, std::to_wstring(player1Score), 2);

	gfx->renderCharacters(418, 10, 1.0f, 1.0f, 1.0f, 1.0f, std::to_wstring(player2Score), 2);


	gfx->FillCircle(ballX, ballY, 5, 1.0f, 1.0f, 1.0f, 1.0f);
}
