#include "Battery.h"
#include <iostream>
#include <thread>
#include <chrono>

Battery::Battery(int startX, int startY, int rockets, int reload)
    : x(startX), y(startY), alive(true), reloading(false), numRockets(rockets), reloadTime(reload) {}

void Battery::move(int dx, int dy) {
    x += dx;
    y += dy;
}

void Battery::reload() {
    reloading = true;
    // Simular tempo de recarga aleat�rio de 1/10 s a 1/2 s
    int reloadDuration = 100 + rand() % 400;
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    reloading = false;
    numRockets = capacity; // Recarregou completamente
}

void initializeBatteries(DifficultyLevel level, std::vector<Battery>& batteries) {
    batteries.push_back(Battery(10, 2, 0, 0)); // Bateria 0
    batteries.push_back(Battery(10, 8, 0, 0)); // Bateria 1

    switch (level) {
    case FACIL:
        // Configura��es para o n�vel f�cil
        batteries[0].capacity = 3;
        batteries[0].reloadTime = 500;
        batteries[1].capacity = 3;
        batteries[1].reloadTime = 500;
        break;
    case MEDIO:
        // Configura��es para o n�vel m�dio
        batteries[0].capacity = 10;
        batteries[0].reloadTime = 1000;
        batteries[1].capacity = 10;
        batteries[1].reloadTime = 1000;
        break;
    case DIFICIL:
        // Configura��es para o n�vel dif�cil
        batteries[0].capacity = 20;
        batteries[0].reloadTime = 500;
        batteries[1].capacity = 20;
        batteries[1].reloadTime = 500;
        break;
    }
}

void Battery::batteryLogic(Battery& otherBattery, std::mutex& mtx) {
    while (alive) {
        // L�gica para movimento da bateria

        // Verificando se precisa recarregar e espere, se necess�rio
        if (reloading) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            continue;
        }

        // Verificando se a outra bateria est� atravessando a ponte e aguarde, se necess�rio
        if (otherBattery.reloading) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            continue;
        }

        // L�gica para disparar foguetes

        if (numRockets > 0) {
            mtx.lock();
            // Dispare um foguete
            numRockets--;
            mtx.unlock();
            // Simulando o tempo de disparo
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        } else {
            reload();
        }
    }
}


