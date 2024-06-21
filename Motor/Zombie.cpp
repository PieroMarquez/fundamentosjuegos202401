#include "Zombie.h"

Zombie::Zombie()
{
}

Zombie::~Zombie()
{
}

void Zombie::init(float speed, glm::vec2 position)
{
	this->speed = speed;
	this->position = position;
	color.set(0, 255, 0, 255);
	direction = glm::vec2(0.0f, -1.0f);
}

void Zombie::update(vector<string>& levelData, vector<Human*>& humans, vector<Zombie*>& zombies)
{
    // Movimiento aleatorio o basado en alg�n criterio espec�fico
    int randomDirection = rand() % 4; // Genera un n�mero aleatorio entre 0 y 3

    switch (randomDirection) {
    case 0:
        direction = glm::vec2(0.0f, -1.0f); // Mover hacia arriba
        break;
    case 1:
        direction = glm::vec2(0.0f, 1.0f); // Mover hacia abajo
        break;
    case 2:
        direction = glm::vec2(-1.0f, 0.0f); // Mover hacia la izquierda
        break;
    case 3:
        direction = glm::vec2(1.0f, 0.0f); // Mover hacia la derecha
        break;
    default:
        break;
    }

    // Aplica la velocidad al movimiento
    position += direction * speed;

    // L�gica de colisi�n con el nivel
    if (collideWithLevel(levelData)) {
        // Cambia la direcci�n cuando colisiona con el nivel
        // Puedes ajustar esto seg�n tus necesidades
        direction = -direction;
    }
}