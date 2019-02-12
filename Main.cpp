#include "Main.h"
#include <wx/settings.h>

MainFrame::MainFrame(const wxString &title) : wxFrame(NULL,wxID_ANY,title, wxPoint(20,wxSystemSettings::GetMetric(wxSYS_SCREEN_Y)/2), wxDefaultSize, wxSTAY_ON_TOP|wxDEFAULT_FRAME_STYLE)
{wxMenu *Help= new wxMenu;
    Help->Append(wxID_ABOUT, wxT("&About\tF1"), wxT("About Application"));
    wxMenuBar *menuBar= new wxMenuBar;
    menuBar->Append(Help, wxT("Help"));
    SetMenuBar(menuBar);

wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
wxArrayString *choices =new wxArrayString;
choices->Add(wxT("Expression"));
choices->Add(wxT("Minterms"));
mode = new wxRadioBox(this, RADIO_BOX, wxT("Mode"), wxDefaultPosition, wxDefaultSize, *choices, 0);
sizer->Add(mode, 0, wxEXPAND);
this->SetSizer(sizer);
sizer->SetSizeHints(this);
expframe= new ExpFrame(this);
sopframe = new SOPFrame(this);
wxCommandEvent evt(wxEVT_COMMAND_RADIOBOX_SELECTED, RADIO_BOX);
ProcessEvent(evt);


}


BEGIN_EVENT_TABLE(MainFrame, wxFrame)
EVT_MENU(wxID_ABOUT, MainFrame::OnAbout)
EVT_RADIOBOX(RADIO_BOX, MainFrame::OnModeSelect)
END_EVENT_TABLE()

void MainFrame::OnAbout(wxCommandEvent& event)
{wxString *msg = new wxString;
*msg<<"Boolean Expression Solver";
wxMessageBox(*msg, wxT("About"), wxCENTER);
}

void MainFrame::OnModeSelect(wxCommandEvent& event)
{

    int ch=event.GetSelection();
switch(ch)
{case 0:
        sopframe->Show(false);
        expframe->Show(true);
break;
case 1:expframe->Show(false);
    sopframe->Show(true);
    }

}




