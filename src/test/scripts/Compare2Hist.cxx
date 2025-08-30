#include "ROOT/RDataFrame.hxx"
#include "RooHist.h"
#include "RooPlot.h"
#include "RooRealVar.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TH1.h"
#include "TPad.h"

#include <string>
void Compare2Hist() {
    using namespace RooFit;
    // from sample file
    auto filePath1{"Sample.root"};
    auto histPath1{"SimMACEPhaseI_M2ee/MRPCSimHit/p0_0"};

    auto file1{new TFile(filePath1, "READ")};
    auto h1{static_cast<TH1D*>(file1->Get(histPath1))};
    // from test file
    auto filePath2{"SimMACEPhaseI_M2ee_test.root"};
    auto treePath2{"G4Run0/MRPCSimHit"};
    auto branchName{"p0_0"};

    ROOT::RDataFrame df0(treePath2, filePath2);
    // auto df{df0};
    auto df{df0.Define("x_0", "x[0]")
                .Define("x_1", "x[1]")
                .Define("x_2", "x[2]")
                .Define("p_0", "p[0]")
                .Define("p_1", "p[1]")
                .Define("p_2", "p[2]")
                .Define("x0_0", "x0[0]")
                .Define("x0_1", "x0[1]")
                .Define("x0_2", "x0[2]")
                .Define("p0_0", "p0[0]")
                .Define("p0_1", "p0[1]")
                .Define("p0_2", "p0[2]")};
    auto h2{df.Histo1D({"h", "Normalized histograms", h1->GetNbinsX(), h1->GetXaxis()->GetXmin(), h1->GetXaxis()->GetXmax()}, branchName)};

    auto i1{h1->Integral()};
    auto i2{h2->Integral()};
    h1->Scale(1 / i1);
    h2->Scale(1 / i2);

    // adjusted residual
    TH1D* resid = (TH1D*)h1->Clone("r");
    resid->SetTitle("Adjusted residual");
    resid->Reset();

    int nBins = h1->GetNbinsX();
    int totalBins = nBins + 2;

    double* array1 = h1->GetArray();
    double* array2 = h2->GetArray();
    double* residArray = resid->GetArray();

    for (int i = 0; i < totalBins; i++) {
        double s = array1[i] + array2[i];
        double d = array1[i] - array2[i];
        if (s == 0.) {
            residArray[i] = 0.;
        } else {
            residArray[i] = (d) / sqrt(s * (1 - s / 2));
        }
    }

    // draw
    TCanvas* c1 = new TCanvas("c1", "c1", 800, 600);
    TPad* pad1 = new TPad("pad1", "pad1", 0, 0.4, 1, 1.0);
    TPad* pad2 = new TPad("pad2", "pad2", 0, 0.0, 1, 0.4);

    pad1->SetBottomMargin(0.06);
    pad2->SetTopMargin(0.06);
    pad2->SetBottomMargin(0.2);

    pad1->Draw();
    pad2->Draw();
    h1->SetLineColor(kRed);
    h1->SetLineWidth(3);
    h2->SetLineColor(kBlue);
    h2->SetLineWidth(3);

    pad1->cd();
    h2->DrawClone();
    h1->DrawClone("SAME");
    pad2->cd();
    resid->Draw();
}
// RooRealVar x1(branchName, branchName, h1->GetXaxis()->GetXmin(), h1->GetXaxis()->GetXmax());
// auto frame1{x1.frame(Title(branchName), Bins(100))};
// auto rh1{new RooHist(*h1)};
// auto rh2{new RooHist(*h2)};
// rh1->SetMarkerColor(kRed);
// rh2->SetMarkerColor(kBlue);
// frame1->addPlotable(rh1, "P");
// frame1->addPlotable(rh2, "P");
// frame1->Draw();
// RooHist* hpull = frame1->pullHist();
// auto frame2{x1.frame(Title("pull"), Bins(100))};
// frame2->addPlotable(hpull);;
// frame2->Draw();
