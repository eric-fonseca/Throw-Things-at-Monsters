#include "Brute.h"

Brute::Brute() : Enemy()
{

}

Brute::Brute(Player target, Texture* deadTex) : Enemy("Brute", 3, 35, target, deadTex)
{
}

Brute::~Brute(void)
{
}
