#ifndef EXP_H_INCLUDED
#define EXP_H_INCLUDED
#include <wx/wx.h>
#include "QMC.h"




class ExpFrame : public wxFrame
{enum{
BTN_0=wxID_HIGHEST+1,
BTN_1,
BTN_OR,
BTN_AND,
BTN_BRACE_OPEN,
BTN_BRACE_CLOSE,
BTN_EVAL,
BTN_CLEAR,
};
public :
ExpFrame(wxFrame *parent);
    wxTextCtrl *tcexp, *tcsol;
    wxString *expression, *solution;
    void OnButton0(wxCommandEvent& event);
    void OnButton1(wxCommandEvent& event);
    void OnButtonAND(wxCommandEvent& event);
    void OnButtonOR(wxCommandEvent& event);
    void OnButtonBraceOpen(wxCommandEvent& event);
    void OnButtonBraceClose(wxCommandEvent& event);
    void OnButtonEval(wxCommandEvent& event);
    void OnButtonClear(wxCommandEvent& event);
    void SetFocusOntcexp();

DECLARE_EVENT_TABLE()
};


#endif // EXP_H_INCLUDED
