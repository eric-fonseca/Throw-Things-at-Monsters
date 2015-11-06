#include "Volatile.h"

Volatile::Volatile() : Enemy()
{
}

Volatile::Volatile(Player target, Texture* deadTex) : Enemy("Volatile", 2, 180, target, deadTex)
{
}

Volatile::~Volatile(void)
{
}

void Volatile::seekPlayer(Player target)
{
	if(health >= 2)
		speed = 0;

	else
		speed = 180;

	Enemy::seekPlayer(target);
}