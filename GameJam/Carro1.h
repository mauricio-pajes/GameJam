#pragma once
#include "Carro.h"
using namespace std;

class Carro1 : public Carro
{
public:
    Carro1(int startX, int startY);
    virtual string GetColorName() const override;
};
