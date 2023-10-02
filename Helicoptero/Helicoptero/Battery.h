#pragma once
#include <vector>
#include <mutex> // Adicione esta linha para incluir a biblioteca <mutex>
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

    Battery(int startX, int startY, int rockets, int reload);
    void move(int dx, int dy);
    void reload();
    void setReloadTime(int newReloadTime) {
        reloadTime = newReloadTime;
    }
    void batteryLogic(Battery& otherBattery, std::mutex& mtx); // Declare a função batteryLogic aqui
};

void initializeBatteries(DifficultyLevel level, std::vector<Battery>& batteries);

#endif

