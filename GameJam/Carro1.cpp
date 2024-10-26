#include "Carro1.h"

Carro1::Carro1(int startX, int startY, CarroContexto ctx)
    : Carro(startX, startY, 0, 0, 0, ctx)
{
}

string Carro1::GetColorName() const
{
    return "Negro";
}

int Carro1::GetTipo() const
{
    return 1;
}
