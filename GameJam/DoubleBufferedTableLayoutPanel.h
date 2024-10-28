#pragma once

using namespace System::Windows::Forms;

namespace GameJam {

    public ref class DoubleBufferedTableLayoutPanel : public TableLayoutPanel
    {
    public:
        DoubleBufferedTableLayoutPanel()
        {
            this->DoubleBuffered = true;
            this->SetStyle(ControlStyles::OptimizedDoubleBuffer |
                ControlStyles::AllPaintingInWmPaint |
                ControlStyles::UserPaint, true);
            this->UpdateStyles();
        }
    };
}
