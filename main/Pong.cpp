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

	player1Score = 0;
	player2Score = 0;
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

	ballSpeed = ballSpeed * 1.001;
	botSpeed = botSpeed + 0.001;


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
			playerY -= 10;
		break;
	case VK_DOWN:
			playerY += 10;
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

	gfx->renderCharacters(318, 10, 1.0f, 1.0f, 1.0f, 1.0f, std::to_wstring(player1Score), 2);

	gfx->renderCharacters(418, 10, 1.0f, 1.0f, 1.0f, 1.0f, std::to_wstring(player2Score), 2);


	gfx->FillCircle(ballX, ballY, 5, 1.0f, 1.0f, 1.0f, 1.0f);
}
