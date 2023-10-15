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
    std::chrono::steady_clock::time_point lastReloadTime;
    bool waitingToCross = false;
    int firingInterval;  

    Battery(int startX, int startY, int rockets, int reload, int interval);
    void move(int dx, int dy);
    void reload();

    std::vector<Rocket> rocketsFired;
    std::chrono::steady_clock::time_point lastFiredTime;

    void fireRocket();
    void updateRockets();

    void fireRocket(int directionX, int directionY) {
        if (numRockets > 0) {
            rocketsFired.push_back(Rocket(x, y, directionX, directionY));
            numRockets--;
        }
    }

    void batteryLogic(Battery& otherBattery); // Declare a fun��o batteryLogic aqui
    void handleReload(Battery& otherBattery);
};


void initializeBatteries(DifficultyLevel level, std::vector<Battery>& batteries);

#endif

