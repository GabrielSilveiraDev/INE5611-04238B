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
    int initialX;
    bool alive;
    bool reloading;
    int numRockets;
    int reloadTime;
    int capacity;
    bool crossingBridge;
    bool crossingDone;
    std::chrono::steady_clock::time_point lastReloadTime;
    bool waitingToCross = false;
    int firingInterval;  

    Battery(int startX, int startY, int rockets, int reload, int interval);
    void move(int dx, int dy);
    void start();
    void updateRocketsLoop();
    void reload();

    std::vector<Rocket> rocketsFired;
    std::chrono::steady_clock::time_point lastFiredTime;

    void fireRocket();
    void updateRockets();

    void batteryLogic(Battery& otherBattery); // Declare a função batteryLogic aqui
    void handleReload(Battery& otherBattery);
};


void initializeBatteries(DifficultyLevel level, std::vector<Battery>& batteries);

#endif

