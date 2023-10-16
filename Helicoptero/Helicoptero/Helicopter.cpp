#include "Helicopter.h"

void Helicopter::MoveUp() {
    if (y > 0) {
        y--;
    }
    else {
        isExploded = true;  // O helicóptero explodiu ao bater no topo
    }
}

void Helicopter::MoveDown() {
    if (y <= 23) {
        y++;
    }
    else {
        isExploded = true;  // O helicóptero explodiu ao bater no chão
    }
}

void Helicopter::MoveLeft() {
    if (x > 0) {
        x--;
    }
}

void Helicopter::MoveRight() {
    if (x < 49) {
        x++;
    }
}

bool Helicopter::IsExploded() {
    return isExploded;
}

bool Helicopter::IsInWall() {
    return (x == 0 || x == 19 || y == 0 || y == 19);
}

bool Helicopter::IsInBase() {
    // Assumindo que a base está na coordenada (19,10)
    return (x == 19 && y == 10);
}
