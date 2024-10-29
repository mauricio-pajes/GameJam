#include "Carro.h"
#include <cstdlib>

Carro::Carro(int startX, int startY, int r, int g, int b, CarroContexto ctx)
    : x(startX), y(startY), colorR(r), colorG(g), colorB(b),
    haLlegado(false), tiempoLlegada(0.0), eliminado(false), contexto(ctx)
{
    if (contexto == CarroContexto::Generador)
    {
        do {
            dx = rand() % 11 - 5;
        } while (dx == 0);

        do {
            dy = rand() % 11 - 5;
        } while (dy == 0);
    }
    else
    {
        dx = 0;
        dy = 0;
    }
}

Carro::~Carro()
{
}

std::string Carro::GetColorName() const
{
    return "Desconocido";
}

int Carro::GetTipo() const
{
    return 0;
}

void Carro::Mover()
{
    if (contexto == CarroContexto::Carrera)
    {
        if (!haLlegado)
        {
            int avance = rand() % 5 + 1;
            x += avance;
        }
    }
    else if (contexto == CarroContexto::Generador)
    {
        x += dx;
        y += dy;
    }
}

bool Carro::HaLlegado(int metaX)
{
    return x >= metaX;
}

void Carro::Rebotar(bool invertirX, bool invertirY)
{
    if (invertirX) dx = -dx;
    if (invertirY) dy = -dy;
}

bool Carro::ChocaCon(Carro* otro)
{
    int distanciaX = x - otro->x;
    int distanciaY = y - otro->y;
    int distanciaCuadrada = distanciaX * distanciaX + distanciaY * distanciaY;
    int radioSumadoX = 180;
    int radioSumadoY = 120;
    return (distanciaX * distanciaX <= radioSumadoX * radioSumadoX) &&
        (distanciaY * distanciaY <= radioSumadoY * radioSumadoY);
}
