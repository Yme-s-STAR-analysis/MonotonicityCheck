#include <iostream>

#include "TPad.h"
#include "TCanvas.h"
#include "TH2F.h"
#include "TString.h"
#include "GraphGenerator.h"

int main() {
    auto g = new GraphGenerator();
    g->Make("r42", "tot", false);
    auto c = new TCanvas();
    c->Clear();
    c->cd();

    TH2F* frame;
    frame = (TH2F*)gPad->DrawFrame(g->x1, g->y1, g->x2, g->y2);
    frame->SetTitle(Form(";sNN;%s", g->GetGraph()->GetName()));
    g->GetGraph()->Draw("epsame");
    c->Print("ut_graph.pdf(");

    c->Clear();
    c->cd();
    g->Shuffle();
    g->GetProperRange();
    g->GetGraph()->Draw("epsame");
    frame = (TH2F*)gPad->DrawFrame(g->x1, g->y1, g->x2, g->y2);
    frame->SetTitle(Form(";sNN;%s", g->GetGraph()->GetName()));
    g->GetGraph()->Draw("epsame");
    c->Print("ut_graph.pdf)");

    return 0;
    


}