#pragma once
#include "item.h"
class BluntWeapon :
	public Item
{
public:
	BluntWeapon(void);
	BluntWeapon(char* n, float w, float s, float d);
	~BluntWeapon(void);

	//Force
	// -What the item is capable of smashing through
	int Force;
};

