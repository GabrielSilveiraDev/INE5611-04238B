#pragma once

class Helicopter {
public:
    int x, y; // Posicao do helicoptero
    bool alive;

    Helicopter(int startX, int startY);

    void move(int dx, int dy);
};
