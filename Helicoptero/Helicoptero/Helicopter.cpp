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
	x--;
}

void Helicopter::MoveRight(int h, int d)
{
	// Move right the helicopter by 1 unit
	x++;
}
