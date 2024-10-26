#pragma once

#include <cstdlib>

using namespace std;

class Carro
{
public:
    int x;
    int y;
    int colorR;
    int colorG;
    int colorB;
    bool haLlegado;
    double tiempoLlegada;

    Carro(int startX, int startY, int r, int g, int b);
    void Mover();
    bool HaLlegado(int metaX);
};
