#pragma once
#include "Carro.h"
#include "Carro1.h"
#include "Carro2.h"
#include "Carro3.h"
#include <vector>
#include <ctime>
#include <cstdlib>
#include "CarroContexto.h"

using namespace std;

namespace GameJam {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class GenerarCarritosForm : public Form
    {
    public:
        GenerarCarritosForm(void)
        {
            InitializeComponent();

            carros = new vector<Carro*>();
            numCarros = 0;
            maxCarros = 20;
            tiempoParaNuevoCarro = 0;
            srand(time(0));

            carros->push_back(new Carro1(50, 50, CarroContexto::Generador));
            carros->push_back(new Carro2(100, 50, CarroContexto::Generador));
            carros->push_back(new Carro3(150, 50, CarroContexto::Generador));
            numCarros = 3;

            movimientoTimer->Start();
            agregarCarroTimer->Start();
        }

    protected:
        ~GenerarCarritosForm()
        {
            if (components)
            {
                delete components;
            }

            for (int i = 0; i < carros->size(); i++)
            {
                delete (*carros)[i];
            }
            delete carros;
        }

    private:
        System::ComponentModel::Container^ components;
        Timer^ movimientoTimer;
        Timer^ agregarCarroTimer;

        vector<Carro*>* carros;
        int numCarros;
        int maxCarros;
        int tiempoParaNuevoCarro;

        void InitializeComponent(void)
        {
            this->components = gcnew System::ComponentModel::Container();
            this->movimientoTimer = gcnew System::Windows::Forms::Timer(this->components);
            this->agregarCarroTimer = gcnew System::Windows::Forms::Timer(this->components);
            this->SuspendLayout();

            
            this->movimientoTimer->Interval = 30; // Milisegundos
            this->movimientoTimer->Tick += gcnew System::EventHandler(this, &GenerarCarritosForm::movimientoTimer_Tick);

            
            this->agregarCarroTimer->Interval = 1000; // 1 segundo
            this->agregarCarroTimer->Tick += gcnew System::EventHandler(this, &GenerarCarritosForm::agregarCarroTimer_Tick);

            
            this->ClientSize = System::Drawing::Size(800, 600);
            this->Name = L"GenerarCarritosForm";
            this->Text = L"Generación Automática de Carritos";
            this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &GenerarCarritosForm::GenerarCarritosForm_Paint);
            this->ResumeLayout(false);
        }

        void movimientoTimer_Tick(Object^ sender, EventArgs^ e)
        {

            MoverYVerificarCarros();

            EliminarCarros();

            this->Invalidate();
        }

        void agregarCarroTimer_Tick(Object^ sender, EventArgs^ e)
        {
            tiempoParaNuevoCarro++;
            if (tiempoParaNuevoCarro >= 20)
            {
                if (numCarros < maxCarros)
                {
                    int tipoCarro = rand() % 3;
                    Carro* nuevoCarro = NULL;
                    int posX = rand() % (this->ClientSize.Width - 30);
                    int posY = rand() % (this->ClientSize.Height - 30);
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
                    carros->push_back(nuevoCarro);
                    numCarros++;
                }
                tiempoParaNuevoCarro = 0;
            }
        }

        void GenerarCarritosForm_Paint(Object^ sender, PaintEventArgs^ e)
        {
            Graphics^ g = e->Graphics;

            for (int i = 0; i < carros->size(); i++)
            {
                Carro* car = (*carros)[i];
                Color carColor = Color::FromArgb(car->colorR, car->colorG, car->colorB);
                SolidBrush^ brush = gcnew SolidBrush(carColor);
                g->FillEllipse(brush, car->x, car->y, 30, 30);
                delete brush;
            }
        }

        void MoverYVerificarCarros()
        {
            for (int i = 0; i < carros->size(); i++)
            {
                Carro* car = (*carros)[i];

                car->Mover();

                if (car->x <= 0 || car->x >= this->ClientSize.Width - 30)
                {
                    car->Rebotar();
                }
                if (car->y <= 0 || car->y >= this->ClientSize.Height - 30)
                {
                    car->Rebotar();
                }
            }

            for (int i = 0; i < carros->size(); i++)
            {
                Carro* carA = (*carros)[i];
                for (int j = i + 1; j < carros->size(); j++)
                {
                    Carro* carB = (*carros)[j];
                    if (carA->ChocaCon(carB))
                    {
                        manejarColision(carA, carB);
                    }
                }
            }
        }

        void manejarColision(Carro* carA, Carro* carB)
        {
            int tipoA = carA->GetTipo();
            int tipoB = carB->GetTipo();

            if ((tipoA == 3 && tipoB == 2) || (tipoA == 2 && tipoB == 3))
            {
                carA->eliminado = true;
                carB->eliminado = true;
            }
            else if ((tipoA == 3 && tipoB == 1) || (tipoA == 1 && tipoB == 3))
            {
                carA->Rebotar();
                carB->Rebotar();
            }
            else if ((tipoA == 2 && tipoB == 1) || (tipoA == 1 && tipoB == 2))
            {
                if (numCarros < maxCarros)
                {
                    int posX = rand() % (this->ClientSize.Width - 30);
                    int posY = rand() % (this->ClientSize.Height - 30);
                    Carro* nuevoCarro = new Carro1(posX, posY, CarroContexto::Generador);
                    carros->push_back(nuevoCarro);
                    numCarros++;
                }
            }
            else
            {
                carA->Rebotar();
                carB->Rebotar();
            }
        }

        void EliminarCarros()
        {
            for (auto it = carros->begin(); it != carros->end(); )
            {
                Carro* car = *it;
                if (car->eliminado)
                {
                    delete car;
                    it = carros->erase(it);
                    numCarros--;
                }
                else
                {
                    ++it;
                }
            }
        }
    };
}
