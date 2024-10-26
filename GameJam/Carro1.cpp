#include "Carro1.h"

Carro1::Carro1(int startX, int startY)
    : Carro(startX, startY, 0, 0, 0)
{
}

string Carro1::GetColorName() const
{
    return "Negro";
}
