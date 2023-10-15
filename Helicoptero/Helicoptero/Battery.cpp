#include "Battery.h"
#include <thread>
#include <chrono>
#include <random>

std::mutex mtx; // Mutex global
std::condition_variable cv; // Variável de condição global
bool bridgeInUse = false; // Indica se a ponte está em uso

// Construtor da classe Battery
Battery::Battery(int startX, int startY, int rockets, int reload, int interval) {
	x = startX;
	y = startY;
	alive = true;
	reloading = false;
	numRockets = rockets;
	reloadTime = reload;
	capacity = rockets;
	crossingBridge = false;
	firingInterval = interval;
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
	auto now = std::chrono::steady_clock::now();
	auto timeSinceLastFired = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastFiredTime).count();
	if (timeSinceLastFired >= firingInterval && numRockets > 0 && alive) {
		rocketsFired.push_back(Rocket(x, y, 0, -1));
		numRockets--;
		lastFiredTime = now;
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
	while (alive) {
		handleReload(otherBattery);
		fireRocket();
		updateRockets();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));  // Pausa geral entre cada loop.
	}
}

void Battery::handleReload(Battery& otherBattery) {
	auto now = std::chrono::steady_clock::now();
	auto timeSinceLastReload = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastReloadTime).count();

	if (numRockets <= 0 && !reloading && !waitingToCross && timeSinceLastReload >= 500) {
		std::unique_lock<std::mutex> lock(mtx);
		if (cv.wait_for(lock, std::chrono::milliseconds(100), [&]() { return !bridgeInUse && !otherBattery.reloading; })) {
			bridgeInUse = true;
			crossingBridge = true;
			waitingToCross = true;
		}
	}

	if (waitingToCross && timeSinceLastReload >= 1000) {
		crossingBridge = false;
		reloading = true;
		reload();
		reloading = false;
		lastReloadTime = now;
		waitingToCross = false;
		crossingBridge = true;
		bridgeInUse = false;
		cv.notify_all();
	}
}



void initializeBatteries(DifficultyLevel level, std::vector<Battery>&batteries) {
	switch (level) {
	case FACIL:
		batteries.push_back(Battery(5, 23, 5, 500, 2000));
		batteries.push_back(Battery(10, 20, 5, 500, 2000));
		break;
	case MEDIO:
		batteries.push_back(Battery(5, 23, 10, 400, 500));
		batteries.push_back(Battery(10, 20, 10, 400, 500));
		break;
	case DIFICIL:
		batteries.push_back(Battery(5, 23, 15, 5000, 1000));
		batteries.push_back(Battery(10, 20, 15, 10000, 1000));
		break;
	}
}
