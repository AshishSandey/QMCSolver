#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED
#include <wx/wx.h>
#include "Exp.h"
#include "SOP.h"


enum{
RADIO_BOX=wxID_HIGHEST+1};

class MainFrame : public wxFrame
{
public:
    MainFrame(const wxString& title);
    wxRadioBox *mode;
    ExpFrame *expframe;
    SOPFrame *sopframe;
    void OnAbout(wxCommandEvent& event);
    void OnModeSelect(wxCommandEvent& event);

DECLARE_EVENT_TABLE()
};


#endif // MAIN_H_INCLUDED
