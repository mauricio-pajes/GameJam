
#pragma once
#include "CarroManager.h"
namespace GameJam {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class FormGeneracion : public System::Windows::Forms::Form
	{
	public:
		FormGeneracion(void)
		{
			InitializeComponent();
			CargarFuentePersonalizada();

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
		~FormGeneracion()
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
		System::Drawing::Text::PrivateFontCollection^ fuentesPersonalizadas;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->SuspendLayout();
			this->components = gcnew System::ComponentModel::Container();
			this->movimientoTimer = gcnew System::Windows::Forms::Timer(this->components);
			this->agregarCarroTimer = gcnew System::Windows::Forms::Timer(this->components);
			this->labelNumCarros = gcnew System::Windows::Forms::Label();
			this->labelSeconds = gcnew System::Windows::Forms::Label();
			this->SuspendLayout();

			this->movimientoTimer->Interval = 30;
			this->movimientoTimer->Tick += gcnew System::EventHandler(this, &FormGeneracion::movimientoTimer_Tick);

			this->agregarCarroTimer->Interval = 1000;
			this->agregarCarroTimer->Tick += gcnew System::EventHandler(this, &FormGeneracion::agregarCarroTimer_Tick);

			this->labelNumCarros->AutoSize = true;
			this->labelNumCarros->Location = System::Drawing::Point(10, 10);
			this->labelNumCarros->Name = L"labelNumCarros";
			this->labelNumCarros->Size = System::Drawing::Size(50, 13);
			this->labelNumCarros->TabIndex = 0;
			this->labelNumCarros->Text = L"Carros: 0";

			this->labelSeconds->AutoSize = true;
			this->labelSeconds->Location = System::Drawing::Point(10, 40);
			this->labelSeconds->Name = L"labelSeconds";
			this->labelSeconds->Size = System::Drawing::Size(65, 13);
			this->labelSeconds->TabIndex = 1;
			this->labelSeconds->Text = L"Segundos: 0";

			this->ClientSize = System::Drawing::Size(800, 600);
			this->Controls->Add(this->labelNumCarros);
			this->Controls->Add(this->labelSeconds);
			this->Name = L"GenerarCarritosForm";
			this->Text = L"Generación Automática de Carritos";
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &FormGeneracion::GenerarCarritosForm_Paint);
			this->Resize += gcnew System::EventHandler(this, &FormGeneracion::GenerarCarritosForm_Resize);
			this->ResumeLayout(false);
			this->PerformLayout();
		}
#pragma endregion

		void CargarFuentePersonalizada()
		{
			fuentesPersonalizadas = gcnew System::Drawing::Text::PrivateFontCollection();
			fuentesPersonalizadas->AddFontFile("KarmaFuture.ttf");

			if (fuentesPersonalizadas->Families->Length > 0)
			{
				this->labelNumCarros->Font = gcnew System::Drawing::Font(fuentesPersonalizadas->Families[0], 12);
				this->labelSeconds->Font = gcnew System::Drawing::Font(fuentesPersonalizadas->Families[0], 12);
			}
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
				if (car != nullptr)
				{
					int pixelSize = 4;
					Color carColor1 = Color::FromArgb(0,car->colorR, car->colorG, car->colorB);
					SolidBrush^ brush = gcnew SolidBrush(carColor1);
					g->FillEllipse(brush, car->x, car->y, 180, 120);
					
					delete brush;

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

					g->FillEllipse(blanco, car->x + 20, car->y + 80, 13 * pixelSize, 13 * pixelSize);
					g->FillEllipse(negro, car->x + 24, car->y + 84, 11 * pixelSize, 11 * pixelSize);
					g->FillEllipse(blanco, car->x + 38, car->y + 98, 4 * pixelSize, 4 * pixelSize);
					g->FillEllipse(blanco, car->x + 126, car->y + 80, 13 * pixelSize, 13 * pixelSize);
					g->FillEllipse(negro, car->x + 130, car->y + 84, 11 * pixelSize, 11 * pixelSize);
					g->FillEllipse(blanco, car->x + 144, car->y + 98, 4 * pixelSize, 4 * pixelSize);

					g->FillRectangle(blanco, car->x + (anchoTotal - 31) * pixelSize, car->y + 15 * pixelSize, 1 * pixelSize, 1 * pixelSize);

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
