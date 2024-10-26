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
    carros[numCarros++] = new Carro2(100, 50, CarroContexto::Generador);
    carros[numCarros++] = new Carro3(150, 50, CarroContexto::Generador);
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

        if (car->x <= 0 || car->x >= width - 30)
        {
            car->Rebotar(true, false);
        }
        if (car->y <= 0 || car->y >= height - 30)
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
    else if ((tipoA == 1 && tipoB == 2) || (tipoA == 2 && tipoB == 1))
    {
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
    }
    else
    {
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
    // Ordenar los �ndices en orden descendente para eliminar sin afectar los �ndices
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
            // Desplazar los carros para llenar el hueco
            for (int j = indice; j < numCarros - 1; j++)
            {
                carros[j] = carros[j + 1];
            }
            carros[numCarros - 1] = NULL; // Establecer el �ltimo elemento a NULL
            numCarros--;
        }
    }
    numCarrosAEliminar = 0; // Reiniciar despu�s de eliminaci�n
}

void CarroManager::AgregarNuevosCarros()
{
    for (int i = 0; i < numCarrosAAgregar; i++)
    {
        carros[numCarros++] = carrosAAgregar[i];
        carrosAAgregar[i] = NULL;
    }
    numCarrosAAgregar = 0; // Reiniciar despu�s de agregar
}

bool CarroManager::posicionValida(int posX, int posY)
{
    for (int i = 0; i < numCarros; i++)
    {
        Carro* car = carros[i];
        int distanciaX = posX - car->x;
        int distanciaY = posY - car->y;
        int distanciaCuadrada = distanciaX * distanciaX + distanciaY * distanciaY;
        int radioSumado = 15 + 15;
        if (distanciaCuadrada <= radioSumado * radioSumado)
            return false; // Hay colisi�n
    }
    return true;
}

void CarroManager::ActualizarLimites(int width, int height)
{
    this->width = width;
    this->height = height;
}

// M�todos auxiliares para verificar movimiento en X e Y
bool CarroManager::EstaMoviendoseEnX(Carro* carro) const
{
    return carro->dx != 0;
}

bool CarroManager::EstaMoviendoseEnY(Carro* carro) const
{
    return carro->dy != 0;
}
