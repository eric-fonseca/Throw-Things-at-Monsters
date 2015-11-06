#pragma once
#include "item.h"
class SharpWeapon :
	public Item
{
public:
	SharpWeapon(void);
	SharpWeapon(char* n, float w, float s, float d);
	~SharpWeapon(void);

	//Piercing
	// -How much the item will penetrate
	int Pierce;
};

