#include "BluntWeapon.h"


BluntWeapon::BluntWeapon(void)
{
}

BluntWeapon::BluntWeapon(char* n, float w, float s, float d){
	Item::Item(n,w,s,d);
}

BluntWeapon::~BluntWeapon(void)
{
}
