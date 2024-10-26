#pragma once
#include "CarreraForm.h"
#include "GenerarCarritosForm.h"

namespace GameJam {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;
    using namespace std;

    public ref class MyForm : public System::Windows::Forms::Form
    {
    public:
        MyForm(void)
        {
            InitializeComponent();
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

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            this->botonCarrera = (gcnew System::Windows::Forms::Button());
            this->botonGenerarCarritos = (gcnew System::Windows::Forms::Button());
            this->etiquetaMenu = (gcnew System::Windows::Forms::Label());
            this->SuspendLayout();

            // 
            // etiquetaMenu
            // 
            this->etiquetaMenu->AutoSize = true;
            this->etiquetaMenu->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 24));
            this->etiquetaMenu->Location = System::Drawing::Point(200, 50);
            this->etiquetaMenu->Name = L"etiquetaMenu";
            this->etiquetaMenu->Size = System::Drawing::Size(100, 37);
            this->etiquetaMenu->TabIndex = 2;
            this->etiquetaMenu->Text = L"Menú";

            // 
            // botonCarrera
            // 
            this->botonCarrera->Location = System::Drawing::Point(80, 150);
            this->botonCarrera->Name = L"botonCarrera";
            this->botonCarrera->Size = System::Drawing::Size(150, 50);
            this->botonCarrera->TabIndex = 0;
            this->botonCarrera->Text = L"Carrera :D";
            this->botonCarrera->UseVisualStyleBackColor = true;
            this->botonCarrera->Click += gcnew System::EventHandler(this, &MyForm::botonCarrera_Click);

            // 
            // botonGenerarCarritos
            // 
            this->botonGenerarCarritos->Location = System::Drawing::Point(280, 150);
            this->botonGenerarCarritos->Name = L"botonGenerarCarritos";
            this->botonGenerarCarritos->Size = System::Drawing::Size(150, 50);
            this->botonGenerarCarritos->TabIndex = 1;
            this->botonGenerarCarritos->Text = L"Generación Automática de Carritos";
            this->botonGenerarCarritos->UseVisualStyleBackColor = true;
            this->botonGenerarCarritos->Click += gcnew System::EventHandler(this, &MyForm::botonGenerarCarritos_Click);

            // 
            // MyForm
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(515, 365);
            this->Controls->Add(this->etiquetaMenu);
            this->Controls->Add(this->botonCarrera);
            this->Controls->Add(this->botonGenerarCarritos);
            this->Name = L"MyForm";
            this->Text = L"MyForm";
            this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
            this->ResumeLayout(false);
            this->PerformLayout();
        }
#pragma endregion

    private:
        void MyForm_Load(Object^ sender, EventArgs^ e)
        {
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
