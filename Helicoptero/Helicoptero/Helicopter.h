#ifndef __HELICOPTER_H__
#define __HELICOPTER_H__
#include <iostream>
#include <thread>
#include <chrono>
#include "Battery.h"
class Helicopter {
public:
	int x; // Posição X do helicóptero na tela
	int y; // Posição Y do helicóptero na tela
	int fuel; // Combustível do helicóptero (ou outro recurso relevante)
	bool isExploded; // Indica se o helicóptero explodiu

	// Construtor para inicializar valores padrão
	Helicopter() : x(0), y(0), fuel(100), isExploded(false) {}

	// Métodos de movimento
	void MoveUp(int x, int y);
	void MoveDown(int x, int y);
	void MoveLeft(int x, int y);
	void MoveRight(int x, int y);

	// Métodos para obter informações sobre o helicóptero
	int GetX() const { return x; }
	int GetY() const { return y; }
	int GetFuel() const { return fuel; }
	bool IsExploded() const { return isExploded; }
	// Check if the helicopter is in the same position as the battery
	bool IsInBattery(const Battery& battery) const {
		return x == battery.x && y == battery.y;
	}
	// Check if the collision with wall happened
	bool IsInWall(int x, int y) const {
		return x == 0 || x == 20 || y == 0 || y == 20;
	}

	// Outros membros e métodos relevantes podem ser adicionados aqui, como funções para movimentar o helicóptero, verificar colisões, etc.
	bool operator==(const Helicopter& other) const {
		return x == other.x && y == other.y;
	};
};
#endif