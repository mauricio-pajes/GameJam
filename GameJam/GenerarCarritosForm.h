#pragma once
#include "CarroManager.h"

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

            this->SetStyle(ControlStyles::UserPaint, true);
            this->SetStyle(ControlStyles::AllPaintingInWmPaint, true);
            this->SetStyle(ControlStyles::DoubleBuffer, true);
            this->UpdateStyles();

            maxCarros = 20;
            int width = this->ClientSize.Width;
            int height = this->ClientSize.Height;
            carroManager = new CarroManager(maxCarros, width, height);

            tiempoParaNuevoCarro = 0;
            secondsCount = 0;

            labelNumCarros->Text = "Carros: " + carroManager->numCarros.ToString();
            labelSeconds->Text = "Segundos: " + secondsCount.ToString();

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

            movimientoTimer->Stop();
            agregarCarroTimer->Stop();

            delete carroManager;
        }

    private:
        System::ComponentModel::Container^ components;
        Timer^ movimientoTimer;
        Timer^ agregarCarroTimer;

        CarroManager* carroManager;
        int maxCarros;
        int tiempoParaNuevoCarro;
        int secondsCount;

        System::Windows::Forms::Label^ labelNumCarros;
        System::Windows::Forms::Label^ labelSeconds;

        void InitializeComponent(void)
        {
            this->components = gcnew System::ComponentModel::Container();
            this->movimientoTimer = gcnew System::Windows::Forms::Timer(this->components);
            this->agregarCarroTimer = gcnew System::Windows::Forms::Timer(this->components);
            this->labelNumCarros = gcnew System::Windows::Forms::Label();
            this->labelSeconds = gcnew System::Windows::Forms::Label();
            this->SuspendLayout();

            
            this->movimientoTimer->Interval = 30;
            this->movimientoTimer->Tick += gcnew System::EventHandler(this, &GenerarCarritosForm::movimientoTimer_Tick);

            
            this->agregarCarroTimer->Interval = 1000;
            this->agregarCarroTimer->Tick += gcnew System::EventHandler(this, &GenerarCarritosForm::agregarCarroTimer_Tick);

            
            this->labelNumCarros->AutoSize = true;
            this->labelNumCarros->Location = System::Drawing::Point(10, 10);
            this->labelNumCarros->Name = L"labelNumCarros";
            this->labelNumCarros->Size = System::Drawing::Size(50, 13);
            this->labelNumCarros->TabIndex = 0;
            this->labelNumCarros->Text = L"Carros: 0";


            this->labelSeconds->AutoSize = true;
            this->labelSeconds->Location = System::Drawing::Point(10, 30);
            this->labelSeconds->Name = L"labelSeconds";
            this->labelSeconds->Size = System::Drawing::Size(65, 13);
            this->labelSeconds->TabIndex = 1;
            this->labelSeconds->Text = L"Segundos: 0";


            this->ClientSize = System::Drawing::Size(800, 600);
            this->Controls->Add(this->labelNumCarros);
            this->Controls->Add(this->labelSeconds);
            this->Name = L"GenerarCarritosForm";
            this->Text = L"Generación Automática de Carritos";
            this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &GenerarCarritosForm::GenerarCarritosForm_Paint);
            this->Resize += gcnew System::EventHandler(this, &GenerarCarritosForm::GenerarCarritosForm_Resize);
            this->ResumeLayout(false);
            this->PerformLayout();
        }

        void movimientoTimer_Tick(Object^ sender, EventArgs^ e)
        {
            carroManager->MoverYVerificarCarros();

            labelNumCarros->Text = "Carros: " + carroManager->numCarros.ToString();

            this->Invalidate();
        }

        void agregarCarroTimer_Tick(Object^ sender, EventArgs^ e)
        {
            tiempoParaNuevoCarro++;
            if (tiempoParaNuevoCarro >= 20)
            {
                carroManager->AgregarCarroAleatorio();
                tiempoParaNuevoCarro = 0;
            }

            secondsCount++;
            labelSeconds->Text = "Segundos: " + secondsCount.ToString();
        }

        void GenerarCarritosForm_Paint(Object^ sender, PaintEventArgs^ e)
        {
            Graphics^ g = e->Graphics;

            for (int i = 0; i < carroManager->numCarros; i++)
            {
                Carro* car = carroManager->carros[i];
                if (car != NULL)
                {
                    Color carColor = Color::FromArgb(car->colorR, car->colorG, car->colorB);
                    SolidBrush^ brush = gcnew SolidBrush(carColor);
                    g->FillEllipse(brush, car->x, car->y, 30, 30);
                    delete brush;
                }
            }
        }

        void GenerarCarritosForm_Resize(Object^ sender, EventArgs^ e)
        {
            int width = this->ClientSize.Width;
            int height = this->ClientSize.Height;
            carroManager->ActualizarLimites(width, height);
        }
    };
}
