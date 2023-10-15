#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>
#include <random>
#include <conio.h>
#include "Rocket.h"
#include "Battery.h"
#include "Helicopter.h"

using namespace std;

// Defina uma variável global para controlar o jogo
bool gameOver = false;

void clearScreen() {
	// Esta função limpa a tela do console (funciona no Windows)
	system("cls");
}

vector<Rocket> rockets;
std::mutex reloadMutex; // Mutex global para controlar a recarga das baterias

void drawGame(const Helicopter& helicopter, const vector<Battery>& batteries) {
	clearScreen();

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

	// Imprimir o tabuleiro
	for (int i = 0; i < 25; i++) {
		for (int j = 0; j < 50; j++) {
			cout << board[i][j] << ' ';
		}
		cout << endl;
	}
}

void handleInput(Helicopter& helicopter) {
	while (!gameOver) {
		if (_kbhit()) {
			char key = _getch();
			switch (key) {
			case 72: // Seta para cima
				helicopter.MoveUp(helicopter.x, helicopter.y);
				break;
			case 80: // Seta para baixo
				helicopter.MoveDown(helicopter.x, helicopter.y);
				break;
			case 75: // Seta para esquerda
				helicopter.MoveLeft(helicopter.x, helicopter.y);
				break;
			case 77: // Seta para direita
				helicopter.MoveRight(helicopter.x, helicopter.y);
				break;
			}
		}
	}
}



int main() {
	srand(time(nullptr));

	// Escolha o nível de dificuldade aqui (FACIL, MEDIO ou DIFICIL)
	DifficultyLevel level = DIFICIL;

	Helicopter helicopter;
	vector<Battery> batteries;

	std::thread inputThread(handleInput, std::ref(helicopter)); // Thread para entradas do usuário

	initializeBatteries(level, batteries);

	mutex mtx;

	vector<thread> batteryThreads;
	vector<thread> rocketThreads;

	batteryThreads.emplace_back(&Battery::batteryLogic, &batteries[0], std::ref(batteries[1]));
	batteryThreads.emplace_back(&Battery::batteryLogic, &batteries[1], std::ref(batteries[0]));
	rocketThreads.emplace_back(&Battery::updateRocketsLoop, &batteries[0]); // Lógica dos foguetes
	rocketThreads.emplace_back(&Battery::updateRocketsLoop, &batteries[1]); // Lógica dos foguetes

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
		cout << "Vitória! Você alcançou o objetivo com sucesso!" << endl;
	}
	else {
		cout << "Derrota! O helicóptero foi abatido ou atingiu uma barreira." << endl;
	}

	return 0;
}
