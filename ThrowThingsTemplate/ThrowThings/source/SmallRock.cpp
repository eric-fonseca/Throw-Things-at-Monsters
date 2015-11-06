#include "SmallRock.h"


SmallRock::SmallRock(void)
{
	BluntWeapon::BluntWeapon("SmallRock", 1.0, 4.0, 1.0);
	Force = 2;
}


SmallRock::~SmallRock(void)
{
}
