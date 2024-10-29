#pragma once
#include "Carro.h"
#include "Carro1.h"
#include "Carro2.h"
#include "Carro3.h"
#include <vector>

#include <ctime>
#include <cstdlib>
#include "CarroContexto.h"

//using namespace std;


namespace GameJam {

    
    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class CarreraForm : public Form
    {
    public:
        CarreraForm(void)
        {
            InitializeComponent();

            this->SetStyle(ControlStyles::UserPaint, true);
            this->SetStyle(ControlStyles::AllPaintingInWmPaint, true);
            this->SetStyle(ControlStyles::DoubleBuffer, true);
            this->UpdateStyles();

            carros = new std::vector<Carro*>();
            ordenLlegada = new std::vector<Carro*>();
            carreraEnCurso = true;
            totalCarrosLlegados = 0;
            metaX = this->ClientSize.Width - 100;


            carros->push_back(new Carro1(50, 100, CarroContexto::Carrera));
            carros->push_back(new Carro2(50, 300, CarroContexto::Carrera));
            carros->push_back(new Carro3(50, 500, CarroContexto::Carrera));

            cronometroTimer->Start();
        }

    protected:
        ~CarreraForm()
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
            delete ordenLlegada;
        }

    private:

        System::ComponentModel::Container^ components;
        Label^ etiquetaCronometro;
        Timer^ cronometroTimer;
        Label^ etiquetaResultado1;
        Label^ etiquetaResultado2;
        Label^ etiquetaResultado3;
        Button^ botonReiniciar;

        double segundos;
        std::vector<Carro*>* carros;
        std::vector<Carro*>* ordenLlegada;
        bool carreraEnCurso;
        int totalCarrosLlegados;
        int metaX;


        void InitializeComponent(void)
        {
            this->etiquetaCronometro = (gcnew System::Windows::Forms::Label());
            this->cronometroTimer = (gcnew System::Windows::Forms::Timer());
            this->etiquetaResultado1 = (gcnew System::Windows::Forms::Label());
            this->etiquetaResultado2 = (gcnew System::Windows::Forms::Label());
            this->etiquetaResultado3 = (gcnew System::Windows::Forms::Label());
            this->botonReiniciar = (gcnew System::Windows::Forms::Button());
            this->SuspendLayout();

            
            this->etiquetaCronometro->AutoSize = true;
            this->etiquetaCronometro->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16));
            this->etiquetaCronometro->Location = System::Drawing::Point(10, 10);
            this->etiquetaCronometro->Name = L"etiquetaCronometro";
            this->etiquetaCronometro->Size = System::Drawing::Size(70, 25);
            this->etiquetaCronometro->TabIndex = 0;
            this->etiquetaCronometro->Text = L"00.00";


            this->etiquetaResultado1->AutoSize = true;
            this->etiquetaResultado1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
            this->etiquetaResultado1->Location = System::Drawing::Point(10, 50);
            
            this->etiquetaResultado1->Name = L"etiquetaResultado1";
            this->etiquetaResultado1->Size = System::Drawing::Size(0, 20);
            this->etiquetaResultado1->TabIndex = 1;
            this->etiquetaResultado1->Text = L"";


            this->etiquetaResultado2->AutoSize = true;
            this->etiquetaResultado2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
            this->etiquetaResultado2->Location = System::Drawing::Point(10, 80);
            this->etiquetaResultado2->Name = L"etiquetaResultado2";
            this->etiquetaResultado2->Size = System::Drawing::Size(0, 20);
            this->etiquetaResultado2->TabIndex = 2;
            this->etiquetaResultado2->Text = L"";


            this->etiquetaResultado3->AutoSize = true;
            this->etiquetaResultado3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
            this->etiquetaResultado3->Location = System::Drawing::Point(10, 110);
            this->etiquetaResultado3->Name = L"etiquetaResultado3";
            this->etiquetaResultado3->Size = System::Drawing::Size(0, 20);
            this->etiquetaResultado3->TabIndex = 3;
            this->etiquetaResultado3->Text = L"";


            this->botonReiniciar->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
            this->botonReiniciar->Location = System::Drawing::Point(700, 10);
            this->botonReiniciar->Name = L"botonReiniciar";
            this->botonReiniciar->Size = System::Drawing::Size(90, 30);
            this->botonReiniciar->TabIndex = 4;
            this->botonReiniciar->Text = L"Reiniciar";
            this->botonReiniciar->UseVisualStyleBackColor = true;
            this->botonReiniciar->Click += gcnew System::EventHandler(this, &CarreraForm::botonReiniciar_Click);

           
            this->cronometroTimer->Interval = 10; // 10 ms para 0.01 segundos
            this->cronometroTimer->Tick += gcnew System::EventHandler(this, &CarreraForm::cronometroTimer_Tick);


            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(800, 400);
            
            this->Controls->Add(this->botonReiniciar);
            this->Controls->Add(this->etiquetaResultado3);
            this->Controls->Add(this->etiquetaResultado2);
            this->Controls->Add(this->etiquetaResultado1);
            this->Controls->Add(this->etiquetaCronometro);
            
            this->Name = L"CarreraForm";
            this->Size = System::Drawing::Size(1200,800);
            this->Text = L"Carrera de Autos";
            this->Load += gcnew System::EventHandler(this, &CarreraForm::CarreraForm_Load);
            this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &CarreraForm::CarreraForm_Paint);
            this->ResumeLayout(false);
            this->PerformLayout();
        }


        void CarreraForm_Load(Object^ sender, EventArgs^ e)
        {
        }

        void IniciarCarrera()
        {

            segundos = 0.0;
            etiquetaCronometro->Text = "00.00";
            carreraEnCurso = true;
            totalCarrosLlegados = 0;

            for (int i = 0; i < carros->size(); i++)
            {
                delete (*carros)[i];
            }
            carros->clear();
            ordenLlegada->clear();

            etiquetaResultado1->Text = "";
            etiquetaResultado2->Text = "";
            etiquetaResultado3->Text = "";

            metaX = this->ClientSize.Width - 100;

            carros->push_back(new Carro1(50, 100, CarroContexto::Carrera));
            carros->push_back(new Carro2(50, 300, CarroContexto::Carrera));
            carros->push_back(new Carro3(50, 500, CarroContexto::Carrera));

            cronometroTimer->Start();
            this->Invalidate();
        }

        void cronometroTimer_Tick(Object^ sender, EventArgs^ e)
        {
            if (carreraEnCurso)
            {
                segundos += 0.01;
                int totalSegundos = segundos;
                int centesimas = (segundos - totalSegundos) * 100;
                etiquetaCronometro->Text = String::Format("{0:D2}.{1:D2}", totalSegundos, centesimas);

                for (int i = 0; i < carros->size(); i++)
                {
                    Carro* car = (*carros)[i];
                    if (!car->haLlegado)
                    {
                        car->Mover();
                        if (car->HaLlegado(metaX))
                        {
                            car->haLlegado = true;
                            car->tiempoLlegada = segundos;
                            totalCarrosLlegados++;
                            ordenLlegada->push_back(car);
                            if (totalCarrosLlegados == carros->size())
                            {
                                carreraEnCurso = false;
                                cronometroTimer->Stop();
                                MostrarResultados();
                            }
                        }
                    }
                }
                this->Invalidate();
            }
        }

        void MostrarResultados()
        {
            for (int i = 0; i < ordenLlegada->size(); i++)
            {
                Carro* car = (*ordenLlegada)[i];
                System::String^ colorCarro = gcnew System::String(car->GetColorName().data());
                System::String^ mensaje = String::Format("{0}º Lugar - Carro {1}: {2:F2} segundos", i + 1, colorCarro, car->tiempoLlegada);
                Label^ etiquetaResultado;
                if (i == 0)
                    etiquetaResultado = etiquetaResultado1;
                else if (i == 1)
                    etiquetaResultado = etiquetaResultado2;
                else if (i == 2)
                    etiquetaResultado = etiquetaResultado3;
                else
                    continue;
                etiquetaResultado->Text = mensaje;
                if (i == 0)
                    etiquetaResultado->ForeColor = Color::Green;
                else if (i == 1)
                    etiquetaResultado->ForeColor = Color::Black;
                else if (i == 2)
                    etiquetaResultado->ForeColor = Color::Red;
            }
        }

        void botonReiniciar_Click(Object^ sender, EventArgs^ e)
        {
            IniciarCarrera();
        }
        void CarreraForm_Paint(Object^ sender, PaintEventArgs^ e)
        {
            Graphics^ g = e->Graphics;
            Pen^ penMeta = gcnew Pen(Color::Black, 3);
            g->DrawLine(penMeta, metaX, 0, metaX, this->ClientSize.Height);
            delete penMeta;
            for (int i = 0; i < carros->size(); i++)
            {

                Carro* car = (*carros)[i];
                Color carColor2 = Color::FromArgb(0,car->colorR, car->colorG, car->colorB);
                SolidBrush^ brush = gcnew SolidBrush(carColor2);
                g->FillEllipse(brush, car->x, car->y, 30, 30);
                delete brush;
                int pixelSize = 4;

                    Color carColor = Color::FromArgb(car->colorR, car->colorG, car->colorB);
                    int anchoTotal = 50;
                    Brush^ colorCarro = gcnew SolidBrush(carColor);
                    Brush^ negro = gcnew SolidBrush(Color::FromArgb(0, 0, 0));
                    Brush^ blanco = gcnew SolidBrush(Color::FromArgb(255, 255, 255));

                    array<Point>^ segmento3 = {
                        Point(car->x + (anchoTotal - 16) * pixelSize, car->y + 0 * pixelSize),
                        Point(car->x + (anchoTotal - 23) * pixelSize, car->y + 0 * pixelSize),
                        Point(car->x + (anchoTotal - 23) * pixelSize, car->y + 4 * pixelSize),
                        Point(car->x + (anchoTotal - 14) * pixelSize, car->y + 4 * pixelSize)
                    };

                    array<Point>^ segmento2 = {
                        Point(car->x + (anchoTotal - 45) * pixelSize, car->y + 0 * pixelSize),
                        Point(car->x + (anchoTotal - 48) * pixelSize, car->y + 0 * pixelSize),
                        Point(car->x + (anchoTotal - 50) * pixelSize, car->y + 13 * pixelSize),
                        Point(car->x + (anchoTotal - 47) * pixelSize, car->y + 13 * pixelSize)
                    };

                    array<Point>^ segmento1 = {
                        Point(car->x + (anchoTotal - 11) * pixelSize, car->y + 0 * pixelSize),
                        Point(car->x + (anchoTotal - 15) * pixelSize, car->y + 0 * pixelSize),
                        Point(car->x + (anchoTotal - 12) * pixelSize, car->y + 6 * pixelSize),
                        Point(car->x + (anchoTotal - 9) * pixelSize, car->y + 4 * pixelSize)
                    };

                    array<Point>^ segmento4 = {
                        Point(car->x + (anchoTotal - 8) * pixelSize, car->y + 5 * pixelSize),
                        Point(car->x + (anchoTotal - 11) * pixelSize, car->y + 7 * pixelSize),
                        Point(car->x + (anchoTotal - 9) * pixelSize, car->y + 11 * pixelSize),
                        Point(car->x + (anchoTotal - 6) * pixelSize, car->y + 9 * pixelSize)
                    };

                    array<Point>^ segmento5 = {
                        Point(car->x + (anchoTotal - 6) * pixelSize, car->y + 10 * pixelSize),
                        Point(car->x + (anchoTotal - 9) * pixelSize, car->y + 12 * pixelSize),
                        Point(car->x + (anchoTotal - 8) * pixelSize, car->y + 13 * pixelSize),
                        Point(car->x + (anchoTotal - 4) * pixelSize, car->y + 13 * pixelSize)
                    };

                    g->FillPolygon(colorCarro, segmento1);
                    g->FillPolygon(colorCarro, segmento2);
                    g->FillPolygon(colorCarro, segmento3);
                    g->FillPolygon(colorCarro, segmento4);
                    g->FillPolygon(colorCarro, segmento5);

                    g->FillRectangle(colorCarro, car->x + (anchoTotal - 44) * pixelSize, car->y + 0 * pixelSize, 4 * pixelSize, 4 * pixelSize);
                    g->FillRectangle(colorCarro, car->x + (anchoTotal - 39) * pixelSize, car->y + 0 * pixelSize, 11 * pixelSize, 4 * pixelSize);

                    g->FillRectangle(colorCarro, car->x + (anchoTotal - 27) * pixelSize, car->y + 0 * pixelSize, 3 * pixelSize, 13 * pixelSize);
                    g->FillRectangle(colorCarro, car->x + (anchoTotal - 27) * pixelSize, car->y + 14 * pixelSize, 3 * pixelSize, 9 * pixelSize);
                    g->FillRectangle(colorCarro, car->x + 10 * pixelSize, car->y + 24 * pixelSize, 38 * pixelSize, 4 * pixelSize);
                    g->FillRectangle(colorCarro, car->x + 28 * pixelSize, car->y + 19 * pixelSize, 20 * pixelSize, 4 * pixelSize);
                    g->FillRectangle(colorCarro, car->x + (anchoTotal - 35) * pixelSize, car->y + 14 * pixelSize, 7 * pixelSize, 4 * pixelSize);
                    g->FillRectangle(colorCarro, car->x + (anchoTotal - 39) * pixelSize, car->y + 14 * pixelSize, 5 * pixelSize, 4 * pixelSize);
                    g->FillRectangle(colorCarro, car->x + (anchoTotal - 43) * pixelSize, car->y + 14 * pixelSize, 3 * pixelSize, 4 * pixelSize);
                    g->FillRectangle(colorCarro, car->x + 0 * pixelSize, car->y + 14 * pixelSize, 6 * pixelSize, 4 * pixelSize);
                    g->FillRectangle(colorCarro, car->x + (anchoTotal - 7) * pixelSize, car->y + 14 * pixelSize, 5 * pixelSize, 4 * pixelSize);
                    g->FillRectangle(colorCarro, car->x + (anchoTotal - 13) * pixelSize, car->y + 14 * pixelSize, 3 * pixelSize, 4 * pixelSize);
                    g->FillRectangle(colorCarro, car->x + (anchoTotal - 17) * pixelSize, car->y + 14 * pixelSize, 4 * pixelSize, 4 * pixelSize);
                    g->FillRectangle(colorCarro, car->x + (anchoTotal - 22) * pixelSize, car->y + 14 * pixelSize, 4 * pixelSize, 4 * pixelSize);
                    g->FillRectangle(colorCarro, car->x + (anchoTotal - 32) * pixelSize, car->y + 19 * pixelSize, 4 * pixelSize, 4 * pixelSize);


                    g->FillRectangle(colorCarro, car->x + 0 * pixelSize, car->y + 19 * pixelSize, 17 * pixelSize, 9 * pixelSize);

                    //izquierda LISTO ------------
                    g->FillEllipse(blanco, car->x + 20, car->y + 80, 13 * pixelSize, 13 * pixelSize);
                    g->FillEllipse(negro, car->x + 24, car->y + 84, 11 * pixelSize, 11 * pixelSize);
                    g->FillEllipse(blanco, car->x + 38, car->y + 98, 4 * pixelSize, 4 * pixelSize);
                    //derechga LISTO ------------
                    g->FillEllipse(blanco, car->x + 126, car->y + 80, 13 * pixelSize, 13 * pixelSize);
                    g->FillEllipse(negro, car->x + 130, car->y + 84, 11 * pixelSize, 11 * pixelSize);
                    g->FillEllipse(blanco, car->x + 144, car->y + 98, 4 * pixelSize, 4 * pixelSize);

                    // Botón 
                    g->FillRectangle(blanco, car->x + (anchoTotal - 31) * pixelSize, car->y + 15 * pixelSize, 1 * pixelSize, 1 * pixelSize);

            }
        }
    };
}

