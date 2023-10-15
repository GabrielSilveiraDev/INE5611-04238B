#pragma once
#include <vector>
#include <mutex> 
#include "Rocket.h"
#ifndef BATTERY_H
#define BATTERY_H

enum DifficultyLevel {
    FACIL,
    MEDIO,
    DIFICIL
};

class Battery {
public:

    int x;
    int y;
    bool alive;
    bool reloading;
    int numRockets;
    int reloadTime;
    int capacity;
    bool crossingBridge;
    int firingInterval;  

    Battery(int startX, int startY, int rockets, int reload, int firingInterval);
    void move(int dx, int dy);
    void reload();

    std::vector<Rocket> rocketsFired;

    void fireRocket();
    void updateRockets();

    void fireRocket(int directionX, int directionY) {
        if (numRockets > 0) {
            rocketsFired.push_back(Rocket(x, y, directionX, directionY));
            numRockets--;
        }
    }

    void batteryLogic(Battery& otherBattery); // Declare a função batteryLogic aqui
};


void initializeBatteries(DifficultyLevel level, std::vector<Battery>& batteries);

#endif

