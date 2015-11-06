#pragma once
#include "enemy.h"

class Volatile : public Enemy
{
public:
	Volatile(void);
	Volatile(Player target, Texture* deadTex);
	~Volatile(void);

	virtual void seekPlayer(Player target);
};

