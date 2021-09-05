#pragma once

#include <wincodec.h>
#include "Graphics.h"


class SpriteSheet
{
	Graphics* gfx;
	ID2D1Bitmap* bmp;
	int spriteWidth, spriteHeight;
	int spritesAccross;

public:

	SpriteSheet(const wchar_t* filename, Graphics* gfx);
	SpriteSheet(const wchar_t* filename, Graphics* gfx, int spriteWidth, int spriteHeight);

	~SpriteSheet();

	void Draw();
	void Draw(int index, int x, int y);
};