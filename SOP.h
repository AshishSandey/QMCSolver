#ifndef SOP_H_INCLUDED
#define SOP_H_INCLUDED
#include <wx/wx.h>
#include <string>
#include "QMC.h"



class SOPFrame : public wxFrame
{
enum{
BTN_CLEAR=wxID_HIGHEST+1,
BTN_EVAL
};
public:
SOPFrame(wxFrame *parent);
wxTextCtrl *ntc;
wxTextCtrl *soptc;
wxTextCtrl *soltc;
void OnButtonEval(wxCommandEvent& event);
void OnButtonClear(wxCommandEvent& event);
DECLARE_EVENT_TABLE()

};


#endif // SOP_H_INCLUDED
