#pragma once

namespace GameJam {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

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
            this->etiquetaMenu->Text = L"Men�";

            // 
            // botonCarrera
            // 
            this->botonCarrera->Location = System::Drawing::Point(80, 150);
            this->botonCarrera->Name = L"botonCarrera";
            this->botonCarrera->Size = System::Drawing::Size(150, 50);
            this->botonCarrera->TabIndex = 0;
            this->botonCarrera->Text = L"Carrera :D";
            this->botonCarrera->UseVisualStyleBackColor = true;

            // 
            // botonGenerarCarritos
            // 
            this->botonGenerarCarritos->Location = System::Drawing::Point(280, 150);
            this->botonGenerarCarritos->Name = L"botonGenerarCarritos";
            this->botonGenerarCarritos->Size = System::Drawing::Size(150, 50);
            this->botonGenerarCarritos->TabIndex = 1;
            this->botonGenerarCarritos->Text = L"Generaci�n Autom�tica de Carritos";
            this->botonGenerarCarritos->UseVisualStyleBackColor = true;

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
            this->ResumeLayout(false);
            this->PerformLayout();
        }
#pragma endregion
    };
}
