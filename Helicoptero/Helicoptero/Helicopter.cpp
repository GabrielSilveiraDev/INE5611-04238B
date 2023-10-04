#include "Helicopter.h"



void Helicopter::MoveUp(int h, int d)
{
	// Move up the helicopter by 1 unit
	y++;
}

void Helicopter::MoveDown(int h, int d)
{
	// Move down the helicopter by 1 unit
	y--;
}

void Helicopter::MoveLeft(int h, int d)
{
	// Move left the helicopter by 1 unit
	if (x <= 0) {
		isExploded = true;
	}
	else if (x > 0) {
		x--;
	}
}

void Helicopter::MoveRight(int h, int d)
{
	// Move right the helicopter by 1 unit
	x++;
}

bool Helicopter::IsInWall(int x, int y)
{
	return x == 0 || x == 40 || y == 0 || y == 20;
}

bool Helicopter::IsInBase()
{
	return x == 20 && y == 10;
}
