#pragma once
#include <string>
#include "CarroContexto.h"

using namespace std;

class Carro
{
public:
    int x;
    int y;

    int colorR;
    int colorG;
    int colorB;

    int dx;
    int dy;

    bool haLlegado;
    double tiempoLlegada;
    bool eliminado;

    CarroContexto contexto;

    Carro(int startX, int startY, int r, int g, int b, CarroContexto ctx);

    virtual ~Carro();

    virtual string GetColorName() const;
    virtual int GetTipo() const;

    void Mover();

    bool HaLlegado(int metaX);
    void Rebotar(bool invertirX, bool invertirY);
    bool ChocaCon(Carro* otro);
};
