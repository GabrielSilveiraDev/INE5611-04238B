#ifndef __HELICOPTER_H__
#define __HELICOPTER_H__
#include <iostream>
#include <thread>
#include <chrono>
#include "Battery.h"
class Helicopter {
public:
	int x; // Posi��o X do helic�ptero na tela a partir da esquerda
	int y; // Posi��o Y do helic�ptero na tela a partir do topo
	int fuel; // Combust�vel do helic�ptero (ou outro recurso relevante)
	int soldiers; // N�mero de soldados no helic�ptero
	bool isExploded; // Indica se o helic�ptero explodiu

	// Construtor para inicializar o helic�ptero na posi��o maxima a esquerda e com o combust�vel m�ximo
	Helicopter() : x(0), y(10), fuel(100), soldiers(10), isExploded(false) {}
		

	// M�todos de movimento
	void MoveUp(int x, int y);
	void MoveDown(int x, int y);
	void MoveLeft(int x, int y);
	void MoveRight(int x, int y);

	// M�todos para obter informa��es sobre o helic�ptero
	int GetX() const { return x; }
	int GetY() const { return y; }
	int GetFuel() const { return fuel; }
	bool IsExploded() const { return isExploded; }

	// Check if the helicopter is in the same position as the battery
	bool IsInBattery(const Battery& battery) const {
		return x == battery.x && y == battery.y;
	}
	// Check if the collision with wall happened
	bool IsInWall(int x, int y);

	// Check if the helicopter arrived at the base
	bool IsInBase();

	// Outros membros e m�todos relevantes podem ser adicionados aqui, como fun��es para movimentar o helic�ptero, verificar colis�es, etc.
	bool operator==(const Helicopter& other) const {
		return x == other.x && y == other.y;
	};
};
#endif