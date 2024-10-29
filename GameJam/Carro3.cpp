#include "Carro3.h"
#include <cstdlib>

Carro3::Carro3(int startX, int startY, CarroContexto ctx)
    : Carro(startX, startY, 0, 0, 0, ctx), nombreColor("Desconocido")
{
    std::vector<ColorNombre> listaColores = {
        {"Rojo", 255, 0, 0},
        {"Verde", 0, 255, 0},
        {"Amarillo", 255, 255, 0},
        {"Cian", 0, 255, 255},
        {"Magenta", 255, 0, 255},
        {"Naranja", 255, 165, 0},
        {"Morado", 128, 0, 128},
        {"Rosa", 255, 192, 203},
        {"Gris", 128, 128, 128},
        {"Blanco", 255, 255, 255},
        {"Marrón", 165, 42, 42}
    };

    if (!listaColores.empty()) {
        int indice = rand() % listaColores.size();
        nombreColor = listaColores[indice].nombre;
        colorR = listaColores[indice].r;
        colorG = listaColores[indice].g;
        colorB = listaColores[indice].b;
    }
}

std::string Carro3::GetColorName() const
{
    return nombreColor;
}

int Carro3::GetTipo() const
{
    return 3;
}
