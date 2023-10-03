#include "Helicopter.h"

// Default constructor
Helicopter::Helicopter()
{
}

void Helicopter::MoveUp(int x, int d)
{
	// Move up the helicopter by 1 unit
	y++;
}

void Helicopter::MoveDown(int x, int y)
{
	// Move down the helicopter by 1 unit
	y--;
}

void Helicopter::MoveLeft(int x, int y)
{
	// Move left the helicopter by 1 unit
	x--;
}

void Helicopter::MoveRight(int x, int y)
{
	// Move right the helicopter by 1 unit
	x++;
}
