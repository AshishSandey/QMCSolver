#include "SOP.h"

SOPFrame::SOPFrame(wxFrame* parent) : wxFrame(parent, wxID_ANY,wxT(""), wxDefaultPosition, wxDefaultSize, wxRESIZE_BORDER)
{   wxPanel *panel = new wxPanel(this);
    wxBoxSizer *topSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *dispSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *ctrSizer = new wxBoxSizer(wxVERTICAL);

    dispSizer->Add(new wxStaticText(panel, wxID_ANY, wxT("No of bits")));
    ntc = new wxTextCtrl(panel, wxID_ANY);
    dispSizer->Add(ntc);
    dispSizer->Add(new wxStaticText(panel, wxID_ANY, wxT("Minterms")));
    soptc = new wxTextCtrl(panel, wxID_ANY);
    dispSizer->Add(soptc, 0, wxEXPAND);
    dispSizer->Add(new wxStaticText(panel, wxID_ANY, wxT("Reduced")));
    soltc = new wxTextCtrl(panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(400,100), wxTE_MULTILINE);
    dispSizer->Add(soltc, 1, wxEXPAND);
    topSizer->Add(dispSizer, 1, wxEXPAND|wxALL, 10);

    ctrSizer->Add(new wxButton(panel, BTN_EVAL, "Evaluate"));
    ctrSizer->Add(new wxButton(panel, BTN_CLEAR, "Clear"));
    topSizer->Add(ctrSizer,0, wxALL, 10);
    panel->SetSizer(topSizer);
    topSizer->SetSizeHints(this);

}

BEGIN_EVENT_TABLE(SOPFrame, wxFrame)
EVT_BUTTON(SOPFrame::BTN_EVAL, SOPFrame::OnButtonEval)
EVT_BUTTON(SOPFrame::BTN_CLEAR, SOPFrame::OnButtonClear)
END_EVENT_TABLE()

void SOPFrame::OnButtonEval(wxCommandEvent& event)
{soltc->Clear();
QMC solver;
int n=wxAtoi(ntc->GetValue());
int hvalue= pow(2,n);
wxString wxsop=soptc->GetValue();
std::string sop = wxString(soptc->GetValue()).ToStdString();
std::string term;
for(int i=0;i<=sop.size(); i++)
{if(sop[i]>='0'&&sop[i]<='9')
term+=sop[i];
else if(term.size())
{
solver.min_terms.push_back(stoi(term));
term.clear();}
}
solver.autovarargs(n);
solver.reduce();

wxString solution;
for(int i=0;i<solver.Solution.size();i++)
{solution = wxString(solver.Solution[i].c_str(),wxConvUTF8);
soltc->AppendText(solution);
soltc->AppendText(wxT("\n"));}}

void SOPFrame::OnButtonClear(wxCommandEvent& event)
{ntc->Clear();
soptc->Clear();
soltc->Clear();
}





