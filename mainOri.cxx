#include <iostream>
#include <fstream>
#include <vector>

#include "TPad.h"
#include "TCanvas.h"
#include "TH2F.h"
#include "TMath.h"
#include "TString.h"
#include "TPaveText.h"

#include "GraphGenerator.h"
#include "FitTool.h"

int main(int argc, char** argv) {
    TH2F* frame;
    auto gg = new GraphGenerator();
    auto ft = new FitTool();
    auto c = new TCanvas();

    const char* obv = argv[1];
    const char* err = argv[2];
    int ord = atoi(argv[3]);
    const char* uniTag = argv[4];    
    int rdSeed = atoi(argv[5]);
    gg->SetSeed(rdSeed);
    gg->Make(obv, err, false);
    // gg->Shuffle(true);
    gg->GetProperRange();
    ft->Reset();

    long n = 100000;
    int step = n / 20;
    for (int i=0; i<n; i++) {
        ft->ReadGraph(gg->GetGraph());
        ft->Fit(ord);
        ft->Analyze();
        if (i%step == 0) {
            std::cout << "[LOG]: Current order (" << ord << "), " << i << " / " << n << "\n";
        }
        gg->Shuffle();
    }
    
    std::cout << "[LOG] Summary: \n";
    std::cout << "\t Number of fit: " << ft->nTotFit << "\n"; 
    std::cout << "\t Number of all positive simulations: " << ft->nAllPos << "\n"; 
    std::cout << "\t Number of all negative simulations: " << ft->nAllNeg << "\n"; 
    std::cout << "\t Number of same sign simulations: " << ft->nSameSign << "\n"; 

    double p = 1 - (ft->nSameSign * 1.0 / ft->nTotFit);
    double sig = TMath::ErfInverse(2 * p - 1) * sqrt(2);
    std::cout << "\t p = " << p << "\n";
    std::cout << "\t Significance: " << sig << "\n";

    c->Clear();
    c->cd();
    auto gori = gg->GetGraph(true);
    auto g = gg->GetGraph();
    frame = (TH2F*)gPad->DrawFrame(gg->x1, gg->y1, gg->x2, gg->y2);
    frame->SetTitle(Form(";sNN;%s", g->GetName()));
    gori->Draw("epsame");

    auto lat = new TPaveText();
    lat->SetX1NDC(0.30);
    lat->SetX2NDC(0.70);
    lat->SetY1NDC(0.12);
    lat->SetY2NDC(0.44);
    lat->SetTextFont(64);
    lat->SetTextSize(10);
    lat->SetTextColor(1);
    TText* ttl = lat->AddText(uniTag);
    ttl->SetTextColor(2);
    lat->AddLine(0.0, 0.9, 1.0, 0.9);
    lat->AddText(Form("Number of entries: %ld | Random Seed: %d", ft->nTotFit, rdSeed));
    lat->AddText(Form("Number of all positive derivative: %ld", ft->nAllPos));
    lat->AddText(Form("Number of all negative derivative: %ld", ft->nAllNeg));
    lat->AddText(Form("Number of all same sign derivative: %ld", ft->nSameSign));
    lat->AddText(Form("p value: %.4f -> Significance: %.4f", p, sig));
    // lat->SetFillColor(0);
    lat->Draw("same");

    c->Print(Form("%s%s_%d_%s.pdf", obv, err, ord, uniTag));

    std::ofstream fout;
    fout.open(Form("%s%s_%d_%s.csv", obv, err, ord, uniTag));
    fout << ft->nTotFit << "," << ft->nAllPos << "," << ft->nAllNeg << "," << ft->nSameSign << "," << p << "," << sig << "\n";
    fout.close();

    return 0;
}