#include "Helicopter.h"



void Helicopter::MoveUp(int h, int d)
{
	// Move up the helicopter by 1 unit and check if it is in the wall
	if (x < 0 || y >= 20) {
		isExploded = true;
	}
	else if (y < 20) {
		y++;
	}
}

void Helicopter::MoveDown(int h, int d)
{
	// Move down the helicopter by 1 unit and check if it is in the wall
	if (x <= 0 || y >= 20) {
		isExploded = true;
	}
	else if (y > 0) {
		y--;
	}
}

void Helicopter::MoveLeft(int h, int d)
{
	// Move left the helicopter by 1 unit
	if (x > 0) {
		x--;
	}
	else if (x <= 0 || y >= 20) {
		isExploded = true;
	}
}

void Helicopter::MoveRight(int h, int d)
{
	// Move right the helicopter by 1 unit and check if it is in the wall
	if (x <= 0 || y >= 20) {
		isExploded = true;
	}
	else if (x < 40) {
		x++;
	}
}

bool Helicopter::IsExploded()
{
	// Check if helicopter is exploded crashing in the wall
	return isExploded;

}

bool Helicopter::IsInWall(int x, int y)
{
	return x == 0 || x == 40 || y == 0 || y == 20;
}

bool Helicopter::IsInBase()
{
	return x == 20 && y == 10;
}
