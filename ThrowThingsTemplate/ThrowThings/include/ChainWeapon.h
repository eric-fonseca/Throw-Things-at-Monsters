#pragma once
#include "item.h"
class ChainWeapon :
	public Item
{
public:
	ChainWeapon(void);
	ChainWeapon(char* n, float w, float s, float d);
	~ChainWeapon(void);

	//Chain length
	// -Max distance you can go from the item without dropping it
	int Length;
};

