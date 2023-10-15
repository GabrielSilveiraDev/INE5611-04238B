#include "Helicopter.h"

// Método para mover o helicóptero para cima
void Helicopter::MoveUp(int x, int y) {
    if (this->y > 0) {  // Verificar se não está no topo
        this->y--;
    }
    else {
        isExploded = true;  // O helicóptero explodiu ao bater no topo
    }
}

// Método para mover o helicóptero para baixo
void Helicopter::MoveDown(int x, int y) {
    if (this->y < 19) {  // Verificar se não está na parte inferior
        this->y++;
    }
    else {
        isExploded = true;  // O helicóptero explodiu ao bater no chão
    }
}

// Método para mover o helicóptero para a esquerda
void Helicopter::MoveLeft(int x, int y) {
    if (this->x > 0) {
        this->x--;
    }
}

// Método para mover o helicóptero para a direita
void Helicopter::MoveRight(int x, int y) {
    if (this->x < 19) {
        this->x++;
    }
}

// Método para verificar se o helicóptero explodiu
bool Helicopter::IsExploded() {
    return isExploded;
}

// Método para verificar se o helicóptero colidiu com a parede (por enquanto, assume-se que a parede é o limite da tela)
bool Helicopter::IsInWall(int x, int y) {
    return (x == 0 || x == 19 || y == 0 || y == 19);
}

// Método para verificar se o helicóptero chegou à base
bool Helicopter::IsInBase() {
    // Assumindo que a base está na coordenada (19,10)
    return (x == 19 && y == 10);
}
