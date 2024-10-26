#include "Carro2.h"

Carro2::Carro2(int startX, int startY, CarroContexto ctx)
    : Carro(startX, startY, 0, 0, 255, ctx) // Azul: RGB(0,0,255)
{
}

string Carro2::GetColorName() const
{
    return "Azul";
}

int Carro2::GetTipo() const
{
    return 2;
}
