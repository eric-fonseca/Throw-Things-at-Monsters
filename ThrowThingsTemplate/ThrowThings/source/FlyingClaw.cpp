#include "FlyingClaw.h"


FlyingClaw::FlyingClaw(void)
{
	ChainWeapon::ChainWeapon("FlyingClaw", 3.0, 3.0, 3.0);
	Length = 5;
}


FlyingClaw::~FlyingClaw(void)
{
}
