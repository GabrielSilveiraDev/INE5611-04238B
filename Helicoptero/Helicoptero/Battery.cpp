#include "Battery.h"
#include <thread>
#include <chrono>
#include <random>

std::mutex mtx; // Mutex global
std::condition_variable cv; // Variável de condição global
bool bridgeInUse = false; // Indica se a ponte está em uso

// Construtor da classe Battery
Battery::Battery(int startX, int startY, int rockets, int reload, int firingInterval) {
    x = startX;
    y = startY;
    alive = true;
    reloading = false;
    numRockets = rockets;
    reloadTime = reload;
    capacity = rockets;
    crossingBridge = false;
}

// Função para mover a bateria
void Battery::move(int dx, int dy) {
    x += dx;
    y += dy;
}

// Função para recarregar a bateria
void Battery::reload() {
    std::this_thread::sleep_for(std::chrono::milliseconds(reloadTime));
    numRockets = capacity;
    reloading = false;
}

void Battery::fireRocket() {
    if (numRockets > 0 && alive) {
        rocketsFired.push_back(Rocket(x, y, 0, -1));
        numRockets--;
    }
}

void Battery::updateRockets() {
    for (Rocket& rocket : rocketsFired) {
        rocket.move();
    }
    rocketsFired.erase(std::remove_if(rocketsFired.begin(), rocketsFired.end(),
        [](const Rocket& rocket) { return rocket.y < 0; }),
        rocketsFired.end());
}

void Battery::batteryLogic(Battery& otherBattery) {
    auto lastFiredTime = std::chrono::system_clock::now();

    while (alive) {
        auto currentTime = std::chrono::system_clock::now();
        auto timeSinceLastFired = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastFiredTime);

        if (numRockets <= 0 && !reloading) {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [&]() { return !bridgeInUse && !otherBattery.reloading; });
            bridgeInUse = true;
            crossingBridge = true;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            crossingBridge = false;
            reloading = true;
            reload();
            reloading = false;
            crossingBridge = true;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            crossingBridge = false;
            bridgeInUse = false;
            cv.notify_all();
        }
        else if (timeSinceLastFired.count() >= firingInterval && numRockets > 0) {
            fireRocket();
            lastFiredTime = currentTime;
        }

        updateRockets();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}


void initializeBatteries(DifficultyLevel level, std::vector<Battery>& batteries) {
    switch (level) {
    case FACIL:
        batteries.push_back(Battery(5, 23, 5, 500, 8000));
        batteries.push_back(Battery(10, 20, 5, 500, 8000));
        break;
    case MEDIO:
        batteries.push_back(Battery(5, 23, 10, 400, 5000));
        batteries.push_back(Battery(10, 20, 10, 400, 5000));
        break;
    case DIFICIL:
        batteries.push_back(Battery(5, 23, 15, 300, 3000));
        batteries.push_back(Battery(10, 20, 15, 300, 3000));
        break;
    }
}
