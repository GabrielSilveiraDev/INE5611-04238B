#pragma once
#include <vector>
#include <mutex> 
#include "Rocket.h"

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
    int firingInterval;  

    Battery(int startX, int startY, int rockets, int reload, int interval);
    void updateRocketsLoop();
    void reload();

    std::vector<Rocket> rocketsFired;

    void fireRocket();
    void updateRockets();

    void batteryLogic(Battery& otherBattery); // Declare a função batteryLogic aqui
    void handleReload(Battery& otherBattery);
};


void initializeBatteries(DifficultyLevel level, std::vector<Battery>& batteries);



