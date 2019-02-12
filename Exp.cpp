#include "Exp.h"
#include <string>

ExpFrame::ExpFrame(wxFrame *parent) : wxFrame(parent, wxID_ANY,wxT(""), wxDefaultPosition, wxDefaultSize, wxRESIZE_BORDER)
{wxPanel *panel=new wxPanel(this, wxID_ANY);

    wxBoxSizer *topSizer= new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *sizer1= new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *dispSizer= new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *ctrSizer= new wxBoxSizer(wxVERTICAL);

    tcexp = new wxTextCtrl(panel,wxID_ANY, wxT(""), wxDefaultPosition, wxSize(400,20));
    tcsol = new wxTextCtrl(panel,wxID_ANY, wxT(""), wxDefaultPosition, wxSize(400,100), wxTE_MULTILINE);
    expression = new wxString;
    solution = new wxString;


    dispSizer->Add(new wxStaticText(panel, wxID_ANY ,wxT("Expression")));
    dispSizer->Add(tcexp, 0, wxEXPAND);
    dispSizer->AddSpacer(20);
    dispSizer->Add(new wxStaticText(panel, wxID_ANY ,wxT("Reduced")));
    dispSizer->Add(tcsol, 1, wxEXPAND);
    sizer1->Add(dispSizer, 1, wxEXPAND);

    sizer1->AddSpacer(40);

    ctrSizer->Add(new wxButton(panel, BTN_EVAL, "Evaluate"));
    ctrSizer->Add(new wxButton(panel, BTN_CLEAR, "Clear"));
    sizer1->Add(ctrSizer,0);

    topSizer->Add(sizer1, 1, wxEXPAND|wxALL, 10);

    wxGridSizer *gs= new wxGridSizer( 2, 3, 3);
    gs->Add(new wxButton(panel, BTN_BRACE_OPEN, "("));
    gs->Add(new wxButton(panel, BTN_BRACE_CLOSE, ")"));
    gs->Add(new wxButton(panel, BTN_0, "0"));
    gs->Add(new wxButton(panel, BTN_1, "1"));
    gs->Add(new wxButton(panel, BTN_OR, "+"));
    gs->Add(new wxButton(panel, BTN_AND, "."));

    topSizer->Add(gs, 0, wxALL, 20);

    panel->SetSizer(topSizer);
    topSizer->SetSizeHints(this);

}

BEGIN_EVENT_TABLE(ExpFrame, wxFrame)
EVT_BUTTON(BTN_0, ExpFrame::OnButton0)
EVT_BUTTON(BTN_1, ExpFrame::OnButton1)
EVT_BUTTON(BTN_AND, ExpFrame::OnButtonAND)
EVT_BUTTON(BTN_OR, ExpFrame::OnButtonOR)
EVT_BUTTON(BTN_EVAL,ExpFrame::OnButtonEval)
EVT_BUTTON(BTN_CLEAR, ExpFrame::OnButtonClear)
EVT_BUTTON(BTN_BRACE_OPEN, ExpFrame::OnButtonBraceOpen)
EVT_BUTTON(BTN_BRACE_CLOSE, ExpFrame::OnButtonBraceClose)
END_EVENT_TABLE()



void ExpFrame::OnButton0(wxCommandEvent& event)
{tcexp->AppendText("0");
SetFocusOntcexp();
}

void ExpFrame::OnButton1(wxCommandEvent& event)
{tcexp->AppendText("1");
SetFocusOntcexp();
}

void ExpFrame::OnButtonOR(wxCommandEvent& event)
{tcexp->AppendText("+");
SetFocusOntcexp();
}

void ExpFrame::OnButtonAND(wxCommandEvent& event)
{tcexp->AppendText(".");
SetFocusOntcexp();
}

void ExpFrame::OnButtonBraceOpen(wxCommandEvent& event)
{tcexp->AppendText("(");
SetFocusOntcexp();
}

void ExpFrame::OnButtonBraceClose(wxCommandEvent& event)
{tcexp->AppendText(")");
SetFocusOntcexp();
}

void ExpFrame::OnButtonEval(wxCommandEvent& event)
{SetFocusOntcexp();
//wxString xx="a\nb\nc\nd";
//tcsol->AppendText(xx);
if(tcexp->IsEmpty())
return;
tcsol->Clear();
*expression=tcexp->GetValue();
QMC solver;
solver.exps=expression->ToStdString();
solver.reduce(solver.exps);

for(int i=0;i<solver.Solution.size();i++)
{solution = new wxString(solver.Solution[i].c_str(),wxConvUTF8);
tcsol->AppendText(*solution);
tcsol->AppendText(wxT("\n"));}

}

void ExpFrame::OnButtonClear(wxCommandEvent& event)
{tcexp->Clear();
tcsol->Clear();
SetFocusOntcexp();
}

void ExpFrame::SetFocusOntcexp()
{tcexp->SetFocusFromKbd();
tcexp->SelectNone();
}



