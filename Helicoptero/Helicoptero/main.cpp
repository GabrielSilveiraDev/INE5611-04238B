#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <conio.h>
#include "Rocket.h"
#include "Battery.h"
#include "Helicopter.h"
#include <windows.h>

using namespace std;

// Variável global para controlar o jogo
bool gameOver = false;

// Matriz para armazenar o estado anterior do tabuleiro
char prevBoard[25][50] = { 0 };


void setCursorPosition(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void clearScreen() {
    // Esta função limpa a tela do console (funciona no Windows)
    system("cls");
}

void drawGame(const Helicopter& helicopter, const vector<Battery>& batteries) {
    char board[25][50];

    // Inicializar o tabuleiro com espaços vazios
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 50; j++) {
            if (i == 24 && (j == 2 || j == 3)) {
                board[i][j] = '_'; // Ponte
            }
            else if (i == 0 || j == 0 || i == 24 || j == 49) {
                board[i][j] = '#'; // Paredes
            }
            else {
                board[i][j] = ' ';
            }
        }
    }

    for (int i = 46; i <= 48; i++) {
        board[13][i] = '_';
    }

    for (int i = 14; i <= 23; i++) {
        board[i][46] = '|';
    }

    // Posicionar o depósito em (1,1)
    board[23][1] = 'D';

    // Posicionar o helicóptero se estiver dentro dos limites
    if (helicopter.x >= 0 && helicopter.x < 50 && helicopter.y >= 0 && helicopter.y < 25) {
        board[helicopter.y][helicopter.x] = 'H';
    }

    // Posicionar as baterias se estiverem dentro dos limites
    for (const Battery& battery : batteries) {
        if (battery.x >= 0 && battery.x < 50 && battery.y >= 0 && battery.y < 25) {
            board[battery.y][battery.x] = 'B';
        }
    }

    // Posicionar os foguetes se estiverem dentro dos limites
    for (const Battery& battery : batteries) {
        for (const Rocket& rocket : battery.rocketsFired) {
            if (rocket.x >= 0 && rocket.x < 50 && rocket.y >= 0 && rocket.y < 25) {
                board[rocket.y][rocket.x] = '|';
            }
        }
    }

    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 50; j++) {
            if (board[i][j] != prevBoard[i][j]) {  // Se a célula mudou
                setCursorPosition(j * 2, i);         // Posicione o cursor
                cout << board[i][j] << ' ';        // Escreva o novo caractere
                prevBoard[i][j] = board[i][j];     // Atualize o board anterior
            }
        }
    }
}

void handleInput(Helicopter& helicopter) {
    while (!gameOver) {
        if (_kbhit()) {
            char key = _getch();
            switch (key) {
            case 72: // Seta para cima
                helicopter.MoveUp();
                break;
            case 80: // Seta para baixo
                helicopter.MoveDown();
                break;
            case 75: // Seta para esquerda
                helicopter.MoveLeft();
                break;
            case 77: // Seta para direita
                helicopter.MoveRight();
                break;
            }
        }
    }
}

int main() {
    srand(time(nullptr));

    DifficultyLevel level = FACIL;

    Helicopter helicopter;
    vector<Battery> batteries;

    std::thread inputThread(handleInput, std::ref(helicopter)); // Thread para entradas do usuário

    initializeBatteries(level, batteries);

    vector<thread> batteryThreads;
    vector<thread> rocketThreads;

    for (size_t i = 0; i < batteries.size(); i++) {
        size_t nextIndex = (i + 1) % batteries.size();  // Isso garante que voltamos ao início depois de atingir o último índice
        batteryThreads.emplace_back(&Battery::batteryLogic, &batteries[i], std::ref(batteries[nextIndex]));
        rocketThreads.emplace_back(&Battery::updateRocketsLoop, &batteries[i]);
    }

    bool victory = false;

    while (!gameOver) {
        
        for (const Battery& battery : batteries) {
            if (helicopter.x == battery.x && helicopter.y == battery.y) {
                gameOver = true;
                victory = false;
                cout << "Derrota! O helicóptero colidiu com uma bateria." << endl;
                break; // Sai do loop de verificação de colisão
            }
        }

        // Condição de vitória
        if (helicopter.x >= 46 && (helicopter.y < 13 && helicopter.y > 10)) {
            gameOver = true;
            victory = true;
        }

        // Condição de derrota por colisão com a plataforma
        if ((helicopter.x >= 46 && helicopter.y >= 13) || (helicopter.x == 1 && helicopter.y == 23) || helicopter.y == 0 || helicopter.y == 24 || helicopter.x == 0 || helicopter.x == 49) {
            gameOver = true;
            victory = false;
        }

        // Checar colisão com foguete
        for (const Battery& battery : batteries) {
            for (const Rocket& rocket : battery.rocketsFired) {
                if (rocket.x == helicopter.x && rocket.y == helicopter.y) {
                    gameOver = true;
                    victory = false;
                }
            }
        }

        drawGame(helicopter, batteries);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    // Encerre o jogo
    gameOver = true;
    clearScreen();

    for (Battery& battery : batteries) {
        battery.alive = false;
    }

    for (thread& t : batteryThreads) {
        t.join();
    }

    inputThread.join();

    for (thread& t : rocketThreads) {
        if (t.joinable()) {
            t.join();
        }
    }

    if (victory) {
        cout << "Vitoria! Voce alcançou o objetivo com sucesso!" << endl;
    }
    else {
        cout << "Derrota! O helicoptero foi abatido ou atingiu uma barreira." << endl;
    }

    return 0;
}
