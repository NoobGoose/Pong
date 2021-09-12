#include "GameController.h"
#include "Graphics.h"
#include "Level1.h"

void Level1::Load()
{
	sprites = new SpriteSheet(L"SpriteSheet.png", gfx, 64, 64);

	frame = 0;

	xPosition = 0.0f;
}
void Level1::Unload()
{
	delete sprites;
}

void Level1::Update(double timeDelta)
{
	xPosition += 20.0f * timeDelta;
	if (xPosition > 800)
		xPosition -= 800.0f;

	frame++;
}

void Level1::Render()
{
	gfx->ClearScreen(0.0f, 0.0f, 0.5f);
	sprites->Draw((frame/10) % 4, xPosition, 100);
}
