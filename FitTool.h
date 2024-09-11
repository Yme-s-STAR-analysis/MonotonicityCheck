#ifndef __FITTOOLH__
#define __FITTOOLH__

#include "TF1.h"
#include "TGraphErrors.h"

class FitTool {

    public:
        FitTool();
        ~FitTool() {}
        
        void Reset();
        void ReadGraph(TGraphErrors* graph) { this->graph = graph; }
        void Fit(int ord);
        void Analyze();
        static constexpr int nFunc = 5;
        long nTotFit;
        long nAllPos;
        long nAllNeg;
        long nSameSign;
    
    private:
        int curOrd;
        TGraphErrors* graph;
        TF1* tfPoly[nFunc];

};

#endif