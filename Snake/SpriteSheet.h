#pragma once

#include <wincodec.h>
#include "Graphics.h"


class SpriteSheet
{
	Graphics* gfx;
	ID2D1Bitmap* bmp;

public:

	SpriteSheet(const wchar_t* filename, Graphics* gfx);

	~SpriteSheet();

	void Draw();
};