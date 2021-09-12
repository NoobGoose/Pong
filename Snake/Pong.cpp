#include "GameController.h"
#include "Graphics.h"
#include "Pong.h"

void Pong::Load()
{
	towardsWall = false;
	ballVelocity = 30;
	playerX = 10;
	playerY = 10;
	ballX = 500;
	ballY = 500;
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

	ballX = ballX + (towardsWall * timeDelta * 100) - (!towardsWall * timeDelta * 100);
	ballY = ballY + (towardsWall * timeDelta * ballVelocity) - (!towardsWall * timeDelta * ballVelocity);


	if (ballX <= 15 || ballX > 795)
		if (Xcollision())
		{
			ballVelocity = -1 / ballVelocity;
			towardsWall = !towardsWall;
		}

		if (ballY < 5 || ballY > 795)
			ballVelocity = -1 / ballVelocity;
}

boolean Pong::Xcollision()
{
	if (ballX <= 15 && ballY > playerY && ballY < playerY + 75)
		return true;
	else if (ballX > 795)
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

	gfx->FillCircle(ballX, ballY, 5, 1.0f, 1.0f, 1.0f, 1.0f);
}
