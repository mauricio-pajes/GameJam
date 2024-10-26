// Carro.cpp
#include "Carro.h"
#include <cstdlib>

Carro::Carro(int startX, int startY, int r, int g, int b, CarroContexto ctx)
    : x(startX), y(startY), colorR(r), colorG(g), colorB(b),
    haLlegado(false), tiempoLlegada(0.0), eliminado(false), contexto(ctx)
{
    if (contexto == CarroContexto::Generador)
    {
        // Inicializar velocidades aleatorias para GenerarCarritosForm
        do {
            dx = rand() % 11 - 5; // Velocidad entre -5 y 5
        } while (dx == 0); // Evitar velocidad cero

        do {
            dy = rand() % 11 - 5; // Velocidad entre -5 y 5
        } while (dy == 0); // Evitar velocidad cero
    }
    else
    {
        dx = 0;
        dy = 0;
    }
}

Carro::~Carro()
{
    // Destructor vacío (no hay recursos dinámicos en la clase base)
}

string Carro::GetColorName() const
{
    return "Desconocido";
}

int Carro::GetTipo() const
{
    return 0; // Tipo base
}

void Carro::Mover()
{
    if (contexto == CarroContexto::Carrera)
    {
        if (!haLlegado)
        {
            int avance = rand() % 5 + 1; // Avanza entre 1 y 5 unidades
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

void Carro::Rebotar()
{
    dx = -dx;
    dy = -dy;
}

bool Carro::ChocaCon(Carro* otro)
{
    int distanciaX = x - otro->x;
    int distanciaY = y - otro->y;
    int distanciaCuadrada = distanciaX * distanciaX + distanciaY * distanciaY;
    int radioSumado = 15 + 15;
    return distanciaCuadrada <= radioSumado * radioSumado;
}
