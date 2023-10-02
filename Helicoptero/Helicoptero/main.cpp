﻿#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>
#include <random>
#include <conio.h>
#include "Battery.h"
#include "Helicopter.h"

using namespace std;

// Defina uma variável global para controlar o jogo
bool gameOver = false;

void clearScreen() {
    // Esta função limpa a tela do console (funciona no Windows)
    system("cls");
}

std::mutex reloadMutex; // Mutex global para controlar a recarga das baterias


void displayGame(const Helicopter& helicopter, const vector<Battery>& batteries) {
    clearScreen();

    // Desenhe o cenário do jogo aqui (pode ser apenas texto)
    cout << "Jogo do helicoptero Antiaereo" << endl;
    cout << "helicoptero: Posicao (" << helicopter.x << ", " << helicopter.y << ")" << endl;

    cout << "Baterias: " << endl;
    for (size_t i = 0; i < batteries.size(); ++i) {
        cout << "Bateria " << i << ": Posicao (" << batteries[i].x << ", " << batteries[i].y << ")";
        if (batteries[i].alive) {
            cout << ", Foguetes: " << batteries[i].numRockets << ", Recarregando: " << (batteries[i].reloading ? "Sim" : "Não") << endl;
        }
        else {
            cout << " (destruída)" << endl;
        }
    }
}

int main() {
    srand(time(nullptr));

    // Escolha o nível de dificuldade aqui (FACIL, MEDIO ou DIFICIL)
    DifficultyLevel level = DIFICIL;

    Helicopter helicopter(0, 5);
    vector<Battery> batteries;

    initializeBatteries(level, batteries);

    mutex mtx;

    vector<thread> batteryThreads;
    for (Battery& battery : batteries) {
        batteryThreads.emplace_back(&Battery::batteryLogic, &battery, std::ref(batteries[1]), std::ref(mtx));
    }

    bool victory = false;

    while (helicopter.alive && !victory) {
        if (_kbhit()) {
            char key = _getch();
            switch (key) {
            case 'w':
                helicopter.move(0, 1); // Mova para cima
                break;
            case 's':
                helicopter.move(0, -1); // Mova para baixo
                break;
            case 'a':
                helicopter.move(-1, 0); // Mova para a esquerda
                break;
            case 'd':
                helicopter.move(1, 0); // Mova para a direita
                break;
            }
        }

        if (helicopter.x >= 20) {
            victory = true;
        }

        if (helicopter.alive) {
            displayGame(helicopter, batteries);
            this_thread::sleep_for(chrono::milliseconds(100));
        }
    }

    // Encerre o jogo
    gameOver = true;

    for (Battery& battery : batteries) {
        battery.alive = false;
    }

    for (thread& t : batteryThreads) {
        t.join();
    }

    // Exiba a mensagem de vitória após o término do jogo
    if (victory) {
        clearScreen();
        cout << "Vitória!" << endl;
    }

    return 0;
}
