#pragma once
#include "Carro.h"

using namespace std;

class Carro2 : public Carro
{
public:
    Carro2(int startX, int startY, CarroContexto ctx);
    virtual string GetColorName() const override;
    virtual int GetTipo() const override;
};
