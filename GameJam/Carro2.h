#pragma once
#include "Carro.h"
using namespace std;

class Carro2 : public Carro
{
public:
    Carro2(int startX, int startY);
    virtual string GetColorName() const override;
};
