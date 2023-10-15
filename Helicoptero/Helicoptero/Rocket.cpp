#include "Rocket.h"

Rocket::Rocket(int startX, int startY, int directionX, int directionY)
    : x(startX), y(startY), dx(directionX), dy(directionY) {}

void Rocket::move() {
    x += dx;
    y += dy;
}
