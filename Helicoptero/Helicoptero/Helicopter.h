#ifndef __HELICOPTER_H__
#define __HELICOPTER_H__

#include "Battery.h"

class Helicopter {
public:
    int x; // Posição X do helicóptero
    int y; // Posição Y do helicóptero
    int soldiers; // Número de soldados no helicóptero
    bool isExploded; // Indica se o helicóptero explodiu

    Helicopter() : x(1), y(10), soldiers(10), isExploded(false) {}

    // Métodos de movimento
    void MoveUp();
    void MoveDown();
    void MoveLeft();
    void MoveRight();

    bool IsExploded();

    int GetX() const { return x; }
    int GetY() const { return y; }

    bool IsInBattery(const Battery& battery) const {
        return x == battery.x && y == battery.y;
    }

    bool IsInWall();
    bool IsInBase();

    bool operator==(const Helicopter& other) const {
        return x == other.x && y == other.y;
    }
};

#endif
