#pragma once

class Rocket {
public:
    int x, y;
    int dx, dy;

    Rocket(int startX, int startY, int directionX, int directionY);
    void move();
};
