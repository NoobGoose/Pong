#pragma once

#define _USE_MATH_DEFINES

#include "GameLevel.h"
#include <math.h>
#include <ctime>

class Pong : public GameLevel
{
	double radiansPi;
	double xPosition, yPosition;
	double wallX, wallY;
	double ballSpeed;
	int frame;

public:

	void Load() override;
	void Unload() override;
	void Render() override;
	void Update(double timeTotal, double timeDelta) override;
	void getWall();

};