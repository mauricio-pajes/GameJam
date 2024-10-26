#include "Carro.h"

Carro::Carro(int startX, int startY, int r, int g, int b)
    : x(startX), y(startY), colorR(r), colorG(g), colorB(b), haLlegado(false), tiempoLlegada(0.0)
{
}

Carro::~Carro()
{
}

string Carro::GetColorName() const
{
    return "Desconocido";
}

void Carro::Mover()
{
    if (!haLlegado)
    {
        int dx = rand() % 5 + 1;
        x += dx;
    }
}

bool Carro::HaLlegado(int metaX)
{
    return x >= metaX;
}
