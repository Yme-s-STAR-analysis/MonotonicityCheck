#include "ArrayHeader.h"
// #include "ArrayHeaderDummy.h" // dummy points
#include "GraphGenerator.h"

GraphGenerator::GraphGenerator(): x1(1), x2(30), y1(-1), y2(1), xFac(1.2), yFac(1.5) {
    rd3 = TRandom3();
}

void GraphGenerator::SetSeed(int seed) {
    rd3.SetSeed(seed);
}

void GraphGenerator::Make(const char* name, const char* err, bool allZero) {
    std::string sName(name);
    std::string sErr(err);
    std::string yLabel;
    float xerr[mArgs::n_Enrpts] = {0.0};
    float *y, *ystat, *ysys;
    float ytot[mArgs::n_Enrpts] = {0.0};
    // read in data points
    if (sName == "r42") {
        y = mArgs::C42_data_cen5_sNN;
        ystat = mArgs::C42_stat_cen5_sNN;
        ysys = mArgs::C42_sys_cen5_sNN;
        yLabel = std::string("C_{4}/C_{2}");
    } else if (sName == "k21") {
        y = mArgs::K21_p_data_cen5_sNN;
        ystat = mArgs::K21_p_stat_cen5_sNN;
        ysys = mArgs::K21_p_sys_cen5_sNN;
        yLabel = std::string("#kappa_{2}/#kappa_{1}");
    } else if (sName == "k31") {
        y = mArgs::K31_p_data_cen5_sNN;
        ystat = mArgs::K31_p_stat_cen5_sNN;
        ysys = mArgs::K31_p_sys_cen5_sNN;
        yLabel = std::string("#kappa_{3}/#kappa_{1}");
    } else if (sName == "k41") {
        y = mArgs::K41_p_data_cen5_sNN;
        ystat = mArgs::K41_p_stat_cen5_sNN;
        ysys = mArgs::K41_p_sys_cen5_sNN;
        yLabel = std::string("#kappa_{4}/#kappa_{1}");
    } else {
        std::cout << "[ERROR] Invalid name received (" << name << ")!\n";
        return;
    }

    // read in error (depending on the specified error mode)
    if (sErr == "stat") {
        for (int i=0; i<mArgs::n_Enrpts; i++) { i[ytot] = i[ystat]; }
    } else if (sErr == "sys") {
        for (int i=0; i<mArgs::n_Enrpts; i++) { i[ytot] = i[ysys]; }
    } else if (sErr == "tot") {
        for (int i=0; i<mArgs::n_Enrpts; i++) { 
            i[ytot] = sqrt(TMath::Sq(i[ystat]) + TMath::Sq(i[ysys]));
        }
    }
    for (int i=0; i<mArgs::n_Enrpts; i++) {
        i[x] = mArgs::sNN_RHIC[i];
        i[xerr] = 0.0;
        if (allZero) { i[y] = 0.0; }
        // copy the values for range calculation
        this->x[i] = x[i];
        this->xerr[i] = xerr[i];
        this->y[i] = y[i];
        this->ytot[i] = ytot[i];
    }

    // make graph
    graph = new TGraphErrors(mArgs::n_Enrpts, x, y, xerr, ytot);
    graph->SetName(yLabel.c_str()); // read out this string when draw frame
    graph->SetMarkerStyle(20);
    graph->SetMarkerColor(1);
    graph->SetMarkerSize(1.8);

    graphOri = new TGraphErrors(mArgs::n_Enrpts, x, y, xerr, ytot);
    graphOri->SetName("Ori");
    graphOri->SetMarkerStyle(20);
    graphOri->SetMarkerColor(1);
    graphOri->SetMarkerSize(1.8);

    GetProperRange();
}

void GraphGenerator::GetProperRange() {
    double* y = graph->GetY();
    double* ytot = graph->GetEY();
    float mUp=-999, mLow=999;
    for (int i=0; i<mArgs::n_Enrpts; i++) {
        mUp = mUp > i[y] + i[ytot] ? mUp : i[y] + i[ytot];
        mLow = mLow < i[y] - i[ytot] ? mLow : i[y] - i[ytot];
    }
    auto xMean = 0.5 * (x[0] + x[mArgs::n_Enrpts-1]);
    auto xDiff = xMean - x[0];
    x1 = xMean - xDiff*xFac;
    x2 = xMean + xDiff*xFac;
    auto yMean = 0.5 * (mUp + mLow);
    auto yDiff = yMean - mLow;
    y1 = yMean - yDiff*yFac;
    y2 = yMean + yDiff*yFac;
}

void GraphGenerator::Shuffle(bool changeOri) {
    double* y = graphOri->GetY();
    double* yerr = graphOri->GetEY();
    for (int i=0; i<mArgs::n_Enrpts; i++) {
        auto yNew = rd3.Gaus(i[y], i[yerr]);
        graph->SetPointY(i, yNew);
        if (changeOri) { graphOri->SetPointY(i, yNew); }
    }
}