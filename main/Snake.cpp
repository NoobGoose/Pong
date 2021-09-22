#include "GameController.h"
#include "Graphics.h"
#include "Snake.h"

void Snake::Load()
{
	fourValueBool = 'D';
}
void Snake::Unload()
{
}

void Snake::Update(double timeDelta)
{

}

void Snake::Render()
{
	gfx->ClearScreen(1.0f, 1.0f, 1.0f);
}
