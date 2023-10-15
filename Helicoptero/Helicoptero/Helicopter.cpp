#include "Helicopter.h"

// M�todo para mover o helic�ptero para cima
void Helicopter::MoveUp(int x, int y) {
    if (this->y > 0) {  // Verificar se n�o est� no topo
        this->y--;
    }
    else {
        isExploded = true;  // O helic�ptero explodiu ao bater no topo
    }
}

// M�todo para mover o helic�ptero para baixo
void Helicopter::MoveDown(int x, int y) {
    if (this->y < 19) {  // Verificar se n�o est� na parte inferior
        this->y++;
    }
    else {
        isExploded = true;  // O helic�ptero explodiu ao bater no ch�o
    }
}

// M�todo para mover o helic�ptero para a esquerda
void Helicopter::MoveLeft(int x, int y) {
    if (this->x > 0) {
        this->x--;
    }
}

// M�todo para mover o helic�ptero para a direita
void Helicopter::MoveRight(int x, int y) {
    if (this->x < 19) {
        this->x++;
    }
}

// M�todo para verificar se o helic�ptero explodiu
bool Helicopter::IsExploded() {
    return isExploded;
}

// M�todo para verificar se o helic�ptero colidiu com a parede (por enquanto, assume-se que a parede � o limite da tela)
bool Helicopter::IsInWall(int x, int y) {
    return (x == 0 || x == 19 || y == 0 || y == 19);
}

// M�todo para verificar se o helic�ptero chegou � base
bool Helicopter::IsInBase() {
    // Assumindo que a base est� na coordenada (19,10)
    return (x == 19 && y == 10);
}
