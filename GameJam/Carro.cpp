#include "Carro.h"

Carro::Carro(int startX, int startY, int r, int g, int b)
{
    x = startX;
    y = startY;
    colorR = r;
    colorG = g;
    colorB = b;
    haLlegado = false;
    tiempoLlegada = 0.0;
}

void Carro::Mover()
{
    if (!haLlegado)
    {
        int deltaX = rand() % 5 + 1;
        x += deltaX;
    }
}

bool Carro::HaLlegado(int metaX)
{
    return x >= metaX;
}
