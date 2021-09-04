#include "GameController.h"
#include "Graphics.h"
#include "Level1.h"

void Level1::Load()
{
	y = 0.0f;
	ySpeed = 0.0f;

	sprites = new SpriteSheet(L"test.png", gfx);
}
void Level1::Unload()
{
	delete sprites;
}
void Level1::Render()
{
	gfx->ClearScreen(0.0f, 0.0f, 0.5f);
	gfx->DrawCircle(
		375.0f, y, 50.0f, 1.0f, 1.0f, 1.0f, 1.0f
	);

	sprites->Draw();
}
void Level1::Update()
{
	ySpeed += 1.0f;
	y += ySpeed;

	if (y > 600)
	{
		y = 600;
		ySpeed = -30.0f;
	}
}