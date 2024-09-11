#include <iostream>
#include "FitTool.h"
#include "ArrayHeader.h"

FitTool::FitTool(): nTotFit(0), nSameSign(0), nAllPos(0), nAllNeg(0), curOrd(1) {
    graph = 0;
    int colors[nFunc] = {
        kGray, 
        kGreen, kRed, kCyan, kBlue
    };
    for (int i=0; i<nFunc; i++) {
        if (i == 0) {
            tfPoly[i] = new TF1(
                "Linear",
                "[0]+[1]*x",
                2, 30
            );
        } else {
            tfPoly[i] = new TF1(
                Form("Polynomial: %d", i+1),
                Form("pol%d", i+1),
                2, 30
            );
        }
        tfPoly[i]->SetLineColor(colors[i]);
    }
}

void FitTool::Reset() {
    nTotFit = 0;
    nAllPos = 0;
    nAllNeg = 0;
    nSameSign = 0;
}

void FitTool::Fit(int ord) {
    if (ord < 1 || ord > 5) { 
        std::cout << "[ERROR] Invalid order (" << ord << ")\n"; 
        return;
    }
    if (!graph) {
        std::cout << "[ERROR] No TGraphErrors read\n"; 
        return;
    }

    curOrd = ord - 1; // 2nd order uses the tfPoly[1] ...
    graph->Fit(tfPoly[curOrd], "RN0Q");
}

void FitTool::Analyze() {
    bool pos;
    double tmp;
    nTotFit ++;
    for (int i=0; i<mArgs::n_Enrpts; i++) {
        tmp = tfPoly[curOrd]->Derivative(mArgs::sNN_RHIC[i]);
        if (i == 0) { 
            pos = tmp > 0; 
            // std::cout << "First point: der = " << tmp << " and pos = " << pos << "\n";
        } // for the first point, set its sign as default
        else {
            // std::cout << i+1 << " point: der = " << tmp << " and pos(this) = " <<  (tmp > 0) << "\n";
            if (pos != (tmp > 0)) { 
                // std::cout << "Different sign found!\n";
                return;
            } 
        } // if the sign changes, just end this iteration
    }
    nSameSign ++;
    if (pos) { nAllPos ++; }
    else { nAllNeg ++; }
}