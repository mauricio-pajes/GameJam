#include "Carro2.h"

Carro2::Carro2(int startX, int startY)
    : Carro(startX, startY, 0, 0, 255)
{
}

string Carro2::GetColorName() const
{
    return "Azul";
}
