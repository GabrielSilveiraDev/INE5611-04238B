#include "Helicopter.h"

Helicopter::Helicopter(int startX, int startY) : x(startX), y(startY), alive(true) {}

void Helicopter::move(int dx, int dy) {
    x += dx;
    y += dy;
}
