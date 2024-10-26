#pragma once
#include "Carro.h"
#include <vector>
#include <string>
using namespace std;

struct ColorNombre {
    string nombre;
    int r;
    int g;
    int b;
};

class Carro3 : public Carro
{
public:
    string nombreColor;
    Carro3(int startX, int startY);
    virtual string GetColorName() const override;
};
