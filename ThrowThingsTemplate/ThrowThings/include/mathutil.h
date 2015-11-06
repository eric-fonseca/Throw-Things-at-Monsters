#include <vix_vector2.h>

float Lerp(float val1, float val2, float amount)
{
	return val1 + (val2 - val1) * amount;
}

Vixen::Vector2 LerpVec(Vixen::Vector2 v1, Vixen::Vector2 v2, float amount)
{
	return Vixen::Vector2(
		Lerp(v1.x, v2.x, amount),
		Lerp(v1.y, v2.y, amount));
}