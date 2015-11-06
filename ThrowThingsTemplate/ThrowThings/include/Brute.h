#pragma once
#include "enemy.h"

class Brute : public Enemy
{
public:
	Brute(void);
	Brute(Player target, Texture* deadTex);
	~Brute(void);
};

