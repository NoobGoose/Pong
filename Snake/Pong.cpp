#include "GameController.h"
#include "Graphics.h"
#include "Pong.h"

double getRadiansPi()
{
	srand(time(NULL));
	int toreturn = (rand() % 200);
	switch (toreturn)
	{
	case 50:
		getRadiansPi();
		break;
	case 100:
		getRadiansPi();
		break;
	case 150:
		getRadiansPi();
		break;
	case 200:
		getRadiansPi();
		break;
	default:
		return (double) toreturn / 100;
	}
}

bool outofbounds(int arg1, int arg2)
{
	if (arg1 <= 0 || arg1 >= 800 || arg2 <= 0 || arg2 >= 600)
		return true;
	else
	{
		return false;
	}
}

void Pong::Load()
{
	frame = 0;
	ballSpeed = 100.0;
	xPosition = 500.0;
	yPosition = 500.0;
	radiansPi = getRadiansPi();


	getWall();
}
void Pong::Unload()
{
}

void Pong::Update(double timeTotal, double timeDelta)
{
	// Ball physics
	// TODO: Handler for corrners
	{
	
		long double delta = sqrt(
			(pow((wallX - xPosition), 2) + 
			(pow((wallY - yPosition), 2))));
		long double distanceRatio = (ballSpeed * timeDelta) / delta;
		double newXPosition = ((xPosition * (1 - distanceRatio)) + (wallX * (distanceRatio)));
		double newYPosition = ((yPosition * (1 - distanceRatio)) + (wallY * (distanceRatio)));

		if (outofbounds(newXPosition, newYPosition))
		{
			{
				double tempY = (-1 / (tan(radiansPi)) * (-100 - xPosition) + yPosition);
				distanceRatio = (ballSpeed * timeDelta) / delta;
				double tempnewXPosition = ((xPosition * (1 - distanceRatio)) + (-100 * (distanceRatio)));
				double tempnewYPosition = ((yPosition * (1 - distanceRatio)) + (tempY * (distanceRatio)));

				if (!(outofbounds(tempnewXPosition, tempnewYPosition)))
				{
					OutputDebugString("Case1\n");

					wallX = tempnewXPosition;
					wallY = tempnewYPosition;
					
				}
				else
				{
					OutputDebugString("Case2\n");

					distanceRatio = (-ballSpeed * timeDelta) / delta;
					double tempnewXPosition = ((xPosition * (1 - distanceRatio)) + (-100 * (distanceRatio)));
					double tempnewYPosition = ((yPosition * (1 - distanceRatio)) + (tempY * (distanceRatio)));

					wallX = tempnewXPosition;
					wallY = tempnewYPosition;
				}
			}


		}
		else
		{
			xPosition = newXPosition;
			yPosition = newYPosition;
		}
	}
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

void Pong::getWall()
{
	double xDelta;
	double yDelta;
	double tempX;
	double tempY;
	double measure;

	switch ((int)(radiansPi * 2))
	{
	case 0:

		measure = -tan(radiansPi * M_PI);

		xDelta = 800 - xPosition;
		yDelta = xDelta * measure;
		tempX = xPosition + xDelta;
		tempY = yPosition + yDelta;
		wallX = tempX;
		wallY = tempY;

		if (tempY <= 0)
		{
			wallY = 0;
			wallX = tempX + (tempY / measure);
		}

		if (tempY >= 600)
		{
			wallY = 600;
			wallX = tempX - (tempY / measure);
		}

		break;

	case 1:

		measure = tan(radiansPi * M_PI);

		xDelta = xPosition;
		yDelta = xDelta * measure;
		tempX = xPosition - xDelta;
		tempY = yPosition + yDelta;
		wallX = tempX;
		wallY = tempY;

		if (tempY <= 0)
		{
			wallY = 0;
			wallX = tempX + (tempY / measure);
		}

		if (tempY >= 600)
		{
			wallY = 600;
			wallX = tempX - (tempY / measure);
		}
		break;

	case 2:

		measure = tan(radiansPi * M_PI);

		xDelta = xPosition;
		yDelta = xDelta * measure;
		tempX = xPosition + xDelta;
		tempY = yPosition + yDelta;
		wallX = tempX;
		wallY = tempY;

		if (tempY <= 0)
		{
			wallY = 0;
			wallX = tempX + (tempY / measure);
		}

		if (tempY >= 600)
		{
			wallY = 600;
			wallX = tempX - (tempY / measure);
		}

		break;

	case 3:

		measure = tan(radiansPi * M_PI);

		xDelta = 800 - xPosition;
		yDelta = xDelta * measure;
		tempX = xPosition + xDelta;
		tempY = yPosition - yDelta;
		wallX = tempX;
		wallY = tempY;

		if (tempY <= 0)
		{
			wallY = 0;
			wallX = tempX + (tempY / measure);
		}

		if (tempY >= 600)
		{
			wallY = 600;
			wallX = tempX - (tempY / measure);
		}

		break;

	default:
		break;
	}
}