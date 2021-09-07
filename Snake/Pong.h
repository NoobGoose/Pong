#pragma once

#include "GameLevel.h"
#include <math.h>

class Pong : public GameLevel
{
	double measure;
	double xPosition, yPosition;
	double newxPosition, newyPosition;
	double ballSpeed;
	int frame;
	bool positiveX;

public:

	void Load() override;
	void Unload() override;
	void Render() override;
	void Update(double timeTotal, double timeDelta) override;
	int getNewPos();

};