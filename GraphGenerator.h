#ifndef __GRPHGNTH__
#define __GRPHGNTH__

#include <iostream>
#include <string>
#include "TMath.h"
#include "TRandom3.h"
#include "TGraphErrors.h"

class GraphGenerator {
    
    public:
        GraphGenerator();
        ~GraphGenerator() {}
        
        void Make(const char* name, const char* err, bool allZero=false);
        void SetScaleX(float val) { xFac = val; }
        void SetScaleY(float val) { yFac = val; }
        TGraphErrors* GetGraph(bool ori=false) { 
            if (ori) { return graphOri; }
            else { return graph; }
        }
        float x1, x2, y1, y2;
        void GetProperRange();
        void Shuffle(bool changeOri=false);
        void SetSeed(int seed);

    private:
        TGraphErrors* graph;
        TGraphErrors* graphOri;
        float xFac, yFac;
        float x[99], xerr[99], y[99], ytot[99];
        TRandom3 rd3;
};

#endif