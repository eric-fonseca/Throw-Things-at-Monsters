#include "SharpWeapon.h"


SharpWeapon::SharpWeapon(void)
{
}

SharpWeapon::SharpWeapon(char* n, float w, float s, float d){
	Item::Item(n,w,s,d);
}

SharpWeapon::~SharpWeapon(void)
{
}
