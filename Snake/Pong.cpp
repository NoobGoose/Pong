#include "GameController.h"
#include "Graphics.h"
#include "Pong.h"

void Pong::Load()
{
	frame = 0;
	ballSpeed = 500.0;
	measure = 35.0;
	xPosition = 500.0;
	yPosition = 500.0;
	positiveX = true;
}
void Pong::Unload()
{
}

void Pong::Update(double timeTotal, double timeDelta)
{
	getNewPos();
}

void Pong::Render()
{
	gfx->ClearScreen(0.0f, 0.0f, 0.0f);
	//Renders Static Objects
	{
		gfx->FillRect(395, 5, 10, 50, 1.0f, 1.0f, 1.0f, 1.0f);
		gfx->FillRect(395, 65, 10, 50, 1.0f, 1.0f, 1.0f, 1.0f);
		gfx->FillRect(395, 125, 10, 50, 1.0f, 1.0f, 1.0f, 1.0f);
		gfx->FillRect(395, 185, 10, 50, 1.0f, 1.0f, 1.0f, 1.0f);
		gfx->FillRect(395, 245, 10, 50, 1.0f, 1.0f, 1.0f, 1.0f);
		gfx->FillRect(395, 305, 10, 50, 1.0f, 1.0f, 1.0f, 1.0f);
		gfx->FillRect(395, 365, 10, 50, 1.0f, 1.0f, 1.0f, 1.0f);
		gfx->FillRect(395, 425, 10, 50, 1.0f, 1.0f, 1.0f, 1.0f);
		gfx->FillRect(395, 485, 10, 50, 1.0f, 1.0f, 1.0f, 1.0f);
		gfx->FillRect(395, 545, 10, 50, 1.0f, 1.0f, 1.0f, 1.0f);
	}

	gfx->FillCircle(xPosition, yPosition, 10, 1.0f, 1.0f, 1.0f, 1.0f);
}

// Ball physics
// TODO: Handler for corrners
int Pong::getNewPos()
{
	// Case +
	if (positiveX)
	{
		OutputDebugStringW(L"PosX\n");

		double tempnewxPos = xPosition +
			sqrt((pow(ballSpeed, 2.0) / (1 + pow(measure, 2.0))));
		double tempnewyPos = ((tempnewxPos - xPosition) / measure) + yPosition;

		if (tempnewxPos >= 800)
		{
			OutputDebugStringW(L"PosX > 800\n");

			//Perpendicular lines
			double xDelta = 800 - xPosition;
			double yDelta = xDelta * measure;
			double wallX = xPosition + xDelta;
			double wallY = yPosition + yDelta;
			double totalDelta = sqrt(pow(xDelta, 2) + pow(yDelta, 2));

			double tempnewxPos = wallX +
				sqrt((pow(ballSpeed - totalDelta, 2.0) / (1 + pow(-measure, 2.0))));
			double tempnewyPos = ((tempnewxPos - wallX) / -measure) + wallY;

			xPosition = tempnewxPos;
			yPosition = tempnewyPos;
			
			measure = -1.0 / measure;
			positiveX = !positiveX;

			return 0;
		}
		if (tempnewyPos <= 0 || tempnewyPos >= 600)
		{
			OutputDebugStringW(L"PosX > 800, Y\n");

			double yDelta = ((yPosition) * (xPosition < 300)) + ((600 - xPosition) * (xPosition > 300)); //We are no longer Yandev
			double xDelta = yDelta / measure;
			double wallX = xPosition + xDelta;
			double wallY = yPosition + yDelta;
			double totalDelta = sqrt(pow(xDelta, 2) + pow(yDelta, 2));

			double tempnewxPos = wallX +
				sqrt((pow(ballSpeed - totalDelta, 2.0) / (1 + pow(-measure, 2.0))));
			double tempnewyPos = ((tempnewxPos - wallX) / -measure) + wallY;

			xPosition = tempnewxPos;
			yPosition = tempnewyPos;

			measure = -1.0 / measure;

			return 0;
		}

		else
		{
			xPosition = tempnewxPos;
			yPosition = tempnewyPos;

			return 0;
		}

	}

	// Case -
	else
	{
		OutputDebugStringW(L"NotPosX\n");

		double tempnewxPos = xPosition -
			sqrt((pow(ballSpeed, 2.0) / (1 + pow(measure, 2.0))));
		double tempnewyPos = ((tempnewxPos - xPosition) / measure) + yPosition;

		if (tempnewxPos <= 0)
		{
			OutputDebugStringW(L"PosX < 0\n");

			//Perpendicular lines
			double xDelta = xPosition;
			double yDelta = xDelta * measure;
			double wallX = xPosition + xDelta;
			double wallY = yPosition + yDelta;
			double totalDelta = sqrt(pow(xDelta, 2) + pow(yDelta, 2));

			double tempnewxPos = wallX +
				sqrt((pow(ballSpeed - totalDelta, 2.0) / (1 + pow(measure, 2.0))));
			double tempnewyPos = ((tempnewxPos - wallX) / measure) + wallY;

			xPosition = tempnewxPos;
			yPosition = tempnewyPos;

			measure = -1.0 / measure;
			positiveX = !positiveX;

			return 0;
		}
		if (tempnewyPos <= 0 || tempnewyPos >= 600)
		{
			OutputDebugStringW(L"PosX < 0, Y\n");

			double yDelta = ((yPosition) * (xPosition < 300)) + ((600 - xPosition) * (xPosition > 300)); //We are no longer Yandev
			double xDelta = yDelta / measure;
			double wallX = xPosition + xDelta;
			double wallY = yPosition + yDelta;
			double totalDelta = sqrt(pow(xDelta, 2) + pow(yDelta, 2));

			double tempnewxPos = wallX +
				sqrt((pow(ballSpeed - totalDelta, 2.0) / (1 + pow(-measure, 2.0))));
			double tempnewyPos = ((tempnewxPos - wallX) / -measure) + wallY;

			xPosition = tempnewxPos;
			yPosition = tempnewyPos;

			measure = -1.0 / measure;

			return 0;
		}

		else
		{
			xPosition = tempnewxPos;
			yPosition = tempnewyPos;

			return 0;
		}
	}
	
};
