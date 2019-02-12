#include "App.h"

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    MainFrame *frame= new MainFrame(wxT("Calculator"));
    SetTopWindow(frame);
    frame->Show(true);
    return true;

}
