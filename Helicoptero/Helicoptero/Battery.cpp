#include "Battery.h"
#include <thread>
#include <chrono>
#include <random>

std::mutex mtx; // Mutex global original
std::condition_variable cv; // Variável de condição global
std::mutex mtx_rocketsFired; // Protege a lista rocketsFired

// Construtor da classe Battery
Battery::Battery(int startX, int startY, int rockets, int reload, int interval) {
    x = startX;
    y = startY;
    initialX = startX;
    alive = true;
    reloading = false;
    numRockets = rockets;
    reloadTime = reload;
    capacity = rockets;
    crossingBridge = false;
    firingInterval = interval;
}



// Lógica da bateria sem os foguetes
void Battery::batteryLogic(Battery& otherBattery) {
    while (alive) {
        handleReload(otherBattery);
        fireRocket();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));  // Pausa geral entre cada loop.
    }
}

// Lógica específica para os foguetes
void Battery::updateRocketsLoop() {
    while (alive) {
        updateRockets();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

// Função para recarregar a bateria
void Battery::reload() {
    std::this_thread::sleep_for(std::chrono::milliseconds(reloadTime));
    numRockets = capacity;
    reloading = false;
}

void Battery::fireRocket() {
    if (reloading) return; // Não atire enquanto estiver recarregando.

    if (numRockets > 0 && alive) {
        {
            std::lock_guard<std::mutex> lock(mtx_rocketsFired);
            rocketsFired.push_back(Rocket(x, y, 0, -1));
        }
        numRockets--;
    }
}


void Battery::updateRockets() {
    std::lock_guard<std::mutex> lock(mtx_rocketsFired);
    for (Rocket& rocket : rocketsFired) {
        rocket.move();
    }
    rocketsFired.erase(std::remove_if(rocketsFired.begin(), rocketsFired.end(),
        [](const Rocket& rocket) { return rocket.y < 0; }),
        rocketsFired.end());
}
void Battery::handleReload(Battery& otherBattery) {


    if (numRockets <= 0 && !reloading) {

        // Movendo a bateria até a posição (23,2)
        while (x > 2) {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            x--;
            if (x == 4) { // Ao chegar próximo da ponte
                std::unique_lock<std::mutex> lock(mtx);
                // Espera até que a outra bateria não esteja cruzando a ponte
                cv.wait(lock, [&]() { return !otherBattery.crossingBridge; });
                crossingBridge = true; // Indica que está cruzando a ponte
            }
        }

        // Recarregando na posição (23,2)
        reloading = true;
        reload();
        reloading = false;

        // Movendo a bateria de volta para sua posição inicial
        while (x < initialX) {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            x++;
            if (x == 4) {
                crossingBridge = false;
                cv.notify_all(); // Informa que terminou de cruzar a ponte
            }
        }
    }
}



void initializeBatteries(DifficultyLevel level, std::vector<Battery>& batteries) {
    switch (level) {
    case FACIL:
        batteries.push_back(Battery(10, 23, 8, 500, 2000));
        batteries.push_back(Battery(15, 23, 12, 500, 2000));
        break;
    case MEDIO:
        batteries.push_back(Battery(10, 23, 10, 300, 1500));
        batteries.push_back(Battery(15, 23, 15, 300, 1500));

        break;
    case DIFICIL:
        batteries.push_back(Battery(10, 23, 15, 200, 1000));
        batteries.push_back(Battery(15, 23, 22, 200, 1000));
        break;
    }
}
