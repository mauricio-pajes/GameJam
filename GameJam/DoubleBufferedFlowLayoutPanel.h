// DoubleBufferedFlowLayoutPanel.h
#pragma once

using namespace System::Windows::Forms;

namespace GameJam {

    public ref class DoubleBufferedFlowLayoutPanel : public FlowLayoutPanel
    {
    public:
        DoubleBufferedFlowLayoutPanel()
        {
            this->DoubleBuffered = true;
            this->SetStyle(ControlStyles::OptimizedDoubleBuffer |
                ControlStyles::AllPaintingInWmPaint |
                ControlStyles::UserPaint, true);
            this->UpdateStyles();
        }
    };
}
