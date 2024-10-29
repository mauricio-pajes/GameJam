#pragma once
#include "Carro.h"
#include "Carro1.h"
#include "Carro2.h"
#include "Carro3.h"

class CarroManager {
public:
    CarroManager(int maxCarros, int width, int height);
    ~CarroManager();

    void MoverYVerificarCarros();
    void manejarColision(Carro* carA, Carro* carB, int indiceA, int indiceB);
    void AgregarCarroAleatorio();
    void EliminarCarros();
    void AgregarNuevosCarros();
    void ActualizarLimites(int width, int height);

    Carro* carros[20];
    int numCarros;
    bool auxRebote = false;

private:
    int maxCarros;
    int width, height;
    int carrosAEliminarIndices[20];
    Carro* carrosAAgregar[20];
    int numCarrosAEliminar;
    int numCarrosAAgregar;

    bool posicionValida(int posX, int posY);

    bool EstaMoviendoseEnX(Carro* carro) const;
    bool EstaMoviendoseEnY(Carro* carro) const;
};
