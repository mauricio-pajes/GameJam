#include "CarroManager.h"
#include <cstdlib>
#include <ctime>

CarroManager::CarroManager(int maxCarros, int width, int height)
    : maxCarros(maxCarros), width(width), height(height), numCarros(0),
    numCarrosAEliminar(0), numCarrosAAgregar(0)
{
    for (int i = 0; i < 20; i++)
    {
        carros[i] = NULL;
        carrosAAgregar[i] = NULL;
        carrosAEliminarIndices[i] = -1;
    }

    srand(time(0));
    carros[numCarros++] = new Carro1(50, 50, CarroContexto::Generador);
    carros[numCarros++] = new Carro2(110, 420, CarroContexto::Generador);
    carros[numCarros++] = new Carro3(500, 450, CarroContexto::Generador);
}

CarroManager::~CarroManager()
{
    for (int i = 0; i < numCarros; i++)
    {
        delete carros[i];
    }
}

void CarroManager::MoverYVerificarCarros()
{
    for (int i = 0; i < numCarros; i++)
    {
        Carro* car = carros[i];
        car->Mover();

        if (car->x <= 0 || car->x >= width - 180)
        {
            car->Rebotar(true, false);
        }
        if (car->y <= 0 || car->y >= height - 120)
        {
            car->Rebotar(false, true);
        }
    }

    for (int i = 0; i < numCarros; i++)
    {
        Carro* carA = carros[i];
        for (int j = i + 1; j < numCarros; j++)
        {
            Carro* carB = carros[j];
            if (carA->ChocaCon(carB))
            {
                manejarColision(carA, carB, i, j);
            }
        }
    }

    EliminarCarros();
    AgregarNuevosCarros();
}

void CarroManager::manejarColision(Carro* carA, Carro* carB, int indiceA, int indiceB)
{
    int tipoA = carA->GetTipo();
    int tipoB = carB->GetTipo();
    bool colisionado = false;
    if ((tipoA == 3 && tipoB == 2) || (tipoA == 2 && tipoB == 3))
    {
        carrosAEliminarIndices[numCarrosAEliminar++] = indiceA;
        carrosAEliminarIndices[numCarrosAEliminar++] = indiceB;
    }
    else if ((tipoA == 3 && tipoB == 1) || (tipoA == 1 && tipoB == 3))
    {
        carA->Rebotar(true, true);
        carB->Rebotar(true, true);
    }
    else if (!colisionado && (tipoA == 1 && tipoB == 2) || (tipoA == 2 && tipoB == 1))
    {
        colisionado = true;
        if (numCarros + numCarrosAAgregar < maxCarros)
        {
            int posX, posY;
            do {
                posX = rand() % (width - 30);
                posY = rand() % (height - 30);
            } while (!posicionValida(posX, posY));

            Carro* nuevoCarro = new Carro1(posX, posY, CarroContexto::Generador);
            carrosAAgregar[numCarrosAAgregar++] = nuevoCarro;
        }
            carA->Rebotar(true,true);
            carB->Rebotar(true, true);
        /*
        if (EstaMoviendoseEnX(carA) == EstaMoviendoseEnX(carB))
        {
            carA->Rebotar(true, false);
            carB->Rebotar(true, false);
        }
        else
        {
            carA->Rebotar(false, true);
            carB->Rebotar(false, true);
        }
        */
        colisionado = false;
    }
    else
    {
        carA->Rebotar(true, true);
        carB->Rebotar(true, true);
       /* if (EstaMoviendoseEnX(carA) == EstaMoviendoseEnX(carB))
        {
            carA->Rebotar(true, false);
            carB->Rebotar(true, false);
        }
        else
        {
            carA->Rebotar(false, true);
            carB->Rebotar(false, true);
        }
        */
    }
}

void CarroManager::AgregarCarroAleatorio()
{
    if (numCarros + numCarrosAAgregar < maxCarros)
    {
        int tipoCarro = rand() % 3;
        Carro* nuevoCarro = NULL;
        int posX, posY;
        do {
            posX = rand() % (width - 30);
            posY = rand() % (height - 30);
        } while (!posicionValida(posX, posY));

        if (tipoCarro == 0)
        {
            nuevoCarro = new Carro1(posX, posY, CarroContexto::Generador);
        }
        else if (tipoCarro == 1)
        {
            nuevoCarro = new Carro2(posX, posY, CarroContexto::Generador);
        }
        else if (tipoCarro == 2)
        {
            nuevoCarro = new Carro3(posX, posY, CarroContexto::Generador);
        }
        carrosAAgregar[numCarrosAAgregar++] = nuevoCarro;
    }
}

void CarroManager::EliminarCarros()
{
    for (int i = 0; i < numCarrosAEliminar - 1; i++)
    {
        for (int j = i + 1; j < numCarrosAEliminar; j++)
        {
            if (carrosAEliminarIndices[i] < carrosAEliminarIndices[j])
            {
                int temp = carrosAEliminarIndices[i];
                carrosAEliminarIndices[i] = carrosAEliminarIndices[j];
                carrosAEliminarIndices[j] = temp;
            }
        }
    }

    for (int i = 0; i < numCarrosAEliminar; i++)
    {
        int indice = carrosAEliminarIndices[i];
        if (indice >= 0 && indice < numCarros)
        {
            delete carros[indice];
            for (int j = indice; j < numCarros - 1; j++)
            {
                carros[j] = carros[j + 1];
            }
            carros[numCarros - 1] = NULL;
            numCarros--;
        }
    }
    numCarrosAEliminar = 0;
}

void CarroManager::AgregarNuevosCarros()
{
    for (int i = 0; i < numCarrosAAgregar; i++)
    {
        carros[numCarros++] = carrosAAgregar[i];
        carrosAAgregar[i] = NULL;
    }
    numCarrosAAgregar = 0;
}

bool CarroManager::posicionValida(int posX, int posY)
{
    for (int i = 0; i < numCarros; i++)
    {
        Carro* car = carros[i];
        int distanciaX = posX - car->x;
        int distanciaY = posY - car->y;
        int distanciaCuadrada = distanciaX * distanciaX + distanciaY * distanciaY;
        int radioSumadoX = 180;
        int radioSumadoY = 120;
        if ((distanciaX * distanciaX <= radioSumadoX * radioSumadoX) &&
            (distanciaY * distanciaY <= radioSumadoY * radioSumadoY)) {
            return false; 
        }
    }
    return true;
}

void CarroManager::ActualizarLimites(int width, int height)
{
    this->width = width;
    this->height = height;
}

bool CarroManager::EstaMoviendoseEnX(Carro* carro) const
{
    return carro->dx != 0;
}

bool CarroManager::EstaMoviendoseEnY(Carro* carro) const
{
    return carro->dy != 0;
}
