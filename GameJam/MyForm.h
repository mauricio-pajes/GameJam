#pragma once
#include "CarreraForm.h"
#include "GenerarCarritosForm.h"
#include "DoubleBufferedTableLayoutPanel.h"
#include "DoubleBufferedFlowLayoutPanel.h"

namespace GameJam {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;
    using namespace System::Drawing::Text;

    public ref class MyForm : public System::Windows::Forms::Form
    {
    public:
        MyForm(void)
        {
            InitializeComponent();
            CargarFuentePersonalizada();

            this->DoubleBuffered = true;
            this->SetStyle(ControlStyles::OptimizedDoubleBuffer |
                ControlStyles::AllPaintingInWmPaint |
                ControlStyles::UserPaint, true);
            this->UpdateStyles();
        }

    protected:
        ~MyForm()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        System::ComponentModel::Container^ components;
        System::Windows::Forms::Button^ botonCarrera;
        System::Windows::Forms::Button^ botonGenerarCarritos;
        System::Windows::Forms::Label^ etiquetaMenu;
        GameJam::DoubleBufferedTableLayoutPanel^ mainLayoutPanel;
        GameJam::DoubleBufferedFlowLayoutPanel^ buttonsFlowPanel;
        PrivateFontCollection^ fuentesPersonalizadas;

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            this->mainLayoutPanel = gcnew GameJam::DoubleBufferedTableLayoutPanel();
            this->botonCarrera = gcnew System::Windows::Forms::Button();
            this->botonGenerarCarritos = gcnew System::Windows::Forms::Button();
            this->etiquetaMenu = gcnew System::Windows::Forms::Label();
            this->buttonsFlowPanel = gcnew GameJam::DoubleBufferedFlowLayoutPanel();
            this->mainLayoutPanel->SuspendLayout();
            this->buttonsFlowPanel->SuspendLayout();
            this->SuspendLayout();

            this->DoubleBuffered = true;
            this->SetStyle(ControlStyles::OptimizedDoubleBuffer |
                ControlStyles::AllPaintingInWmPaint |
                ControlStyles::UserPaint, true);
            this->UpdateStyles();

            this->mainLayoutPanel->ColumnCount = 1;
            this->mainLayoutPanel->RowCount = 3;
            this->mainLayoutPanel->ColumnStyles->Add(gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 100));
            this->mainLayoutPanel->RowStyles->Add(gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 40));
            this->mainLayoutPanel->RowStyles->Add(gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::AutoSize));
            this->mainLayoutPanel->RowStyles->Add(gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 60));
            this->mainLayoutPanel->Dock = System::Windows::Forms::DockStyle::Fill;
            this->mainLayoutPanel->Location = System::Drawing::Point(0, 0);
            this->mainLayoutPanel->Name = L"mainLayoutPanel";
            this->mainLayoutPanel->Size = System::Drawing::Size(600, 365);
            this->mainLayoutPanel->TabIndex = 0;

            this->mainLayoutPanel->BackgroundImage = System::Drawing::Image::FromFile("f1.png");
            this->mainLayoutPanel->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;

            this->etiquetaMenu->AutoSize = true;
            this->etiquetaMenu->Text = L"Menú";
            this->etiquetaMenu->Anchor = System::Windows::Forms::AnchorStyles::None;
            this->etiquetaMenu->BackColor = System::Drawing::Color::FromArgb(200, 255, 255, 255);
            this->etiquetaMenu->ForeColor = System::Drawing::Color::Black;
            this->mainLayoutPanel->Controls->Add(this->etiquetaMenu, 0, 0);

            this->botonCarrera->Name = L"botonCarrera";
            this->botonCarrera->Text = L"Carrera :D";
            this->botonCarrera->UseVisualStyleBackColor = false;
            this->botonCarrera->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->botonCarrera->FlatAppearance->BorderSize = 2;
            this->botonCarrera->FlatAppearance->BorderColor = System::Drawing::Color::Black;
            this->botonCarrera->BackColor = System::Drawing::Color::FromArgb(200, 255, 255, 255);
            this->botonCarrera->Anchor = System::Windows::Forms::AnchorStyles::None;
            this->botonCarrera->Click += gcnew System::EventHandler(this, &MyForm::botonCarrera_Click);
            this->botonCarrera->Margin = System::Windows::Forms::Padding(20, 10, 20, 10);

            this->botonGenerarCarritos->Name = L"botonGenerarCarritos";
            this->botonGenerarCarritos->Text = L"Generación Automática de Carritos";
            this->botonGenerarCarritos->UseVisualStyleBackColor = false;
            this->botonGenerarCarritos->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->botonGenerarCarritos->FlatAppearance->BorderSize = 2;
            this->botonGenerarCarritos->FlatAppearance->BorderColor = System::Drawing::Color::Black;
            this->botonGenerarCarritos->BackColor = System::Drawing::Color::FromArgb(200, 255, 255, 255);
            this->botonGenerarCarritos->Anchor = System::Windows::Forms::AnchorStyles::None;
            this->botonGenerarCarritos->Click += gcnew System::EventHandler(this, &MyForm::botonGenerarCarritos_Click);
            this->botonGenerarCarritos->Margin = System::Windows::Forms::Padding(20, 10, 20, 10);

            this->buttonsFlowPanel->FlowDirection = FlowDirection::LeftToRight;
            this->buttonsFlowPanel->AutoSize = true;
            this->buttonsFlowPanel->Anchor = System::Windows::Forms::AnchorStyles::None;
            this->buttonsFlowPanel->Controls->Add(this->botonCarrera);
            this->buttonsFlowPanel->Controls->Add(this->botonGenerarCarritos);
            this->buttonsFlowPanel->Padding = System::Windows::Forms::Padding(0, 20, 0, 0);
            this->buttonsFlowPanel->BackColor = System::Drawing::Color::Transparent;
            this->mainLayoutPanel->Controls->Add(this->buttonsFlowPanel, 0, 2);

            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(600, 365);
            this->Controls->Add(this->mainLayoutPanel);
            this->Name = L"MyForm";
            this->Text = L"MyForm";
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
            this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
            this->Resize += gcnew System::EventHandler(this, &MyForm::MyForm_Resize);
            this->mainLayoutPanel->ResumeLayout(false);
            this->mainLayoutPanel->PerformLayout();
            this->buttonsFlowPanel->ResumeLayout(false);
            this->buttonsFlowPanel->PerformLayout();
            this->ResumeLayout(false);
            this->PerformLayout();
        }
#pragma endregion

        void CargarFuentePersonalizada()
        {
            fuentesPersonalizadas = gcnew PrivateFontCollection();
            fuentesPersonalizadas->AddFontFile("KarmaFuture.ttf");

            if (fuentesPersonalizadas->Families->Length > 0)
            {
                this->etiquetaMenu->Font = gcnew System::Drawing::Font(fuentesPersonalizadas->Families[0], 24);
                this->botonCarrera->Font = gcnew System::Drawing::Font(fuentesPersonalizadas->Families[0], 12);
                this->botonGenerarCarritos->Font = gcnew System::Drawing::Font(fuentesPersonalizadas->Families[0], 12);
            }
        }

        void AjustarComponentes()
        {
            int anchoFormulario = this->ClientSize.Width;
            int altoFormulario = this->ClientSize.Height;

            this->etiquetaMenu->Font = gcnew System::Drawing::Font(fuentesPersonalizadas->Families[0], Math::Min(anchoFormulario, altoFormulario) / 10);

            int botonAncho = anchoFormulario / 2;
            int botonAlto = altoFormulario / 8;
            int botonFontSize = Math::Min(anchoFormulario, altoFormulario) / 40;

            this->botonCarrera->Size = System::Drawing::Size(botonAncho, botonAlto);
            this->botonCarrera->Font = gcnew System::Drawing::Font(fuentesPersonalizadas->Families[0], botonFontSize);

            this->botonGenerarCarritos->Size = System::Drawing::Size(botonAncho, botonAlto);
            this->botonGenerarCarritos->Font = gcnew System::Drawing::Font(fuentesPersonalizadas->Families[0], botonFontSize);
        }

        void MyForm_Load(Object^ sender, EventArgs^ e)
        {
            AjustarComponentes();
        }

        void MyForm_Resize(Object^ sender, EventArgs^ e)
        {
            AjustarComponentes();
        }

        void botonCarrera_Click(Object^ sender, EventArgs^ e)
        {
            CarreraForm^ carreraForm = gcnew CarreraForm();
            carreraForm->Show();
        }

        void botonGenerarCarritos_Click(Object^ sender, EventArgs^ e)
        {
            GenerarCarritosForm^ generarCarritosForm = gcnew GenerarCarritosForm();
            generarCarritosForm->Show();
        }
    };
}
