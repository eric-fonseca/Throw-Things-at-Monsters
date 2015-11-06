#include "ThrowingKnife.h"


ThrowingKnife::ThrowingKnife(void)
{
	SharpWeapon::SharpWeapon("ThrowingKnife", 1.0, 5.0, 3.0);
	Pierce = 5;
}


ThrowingKnife::~ThrowingKnife(void)
{
}
