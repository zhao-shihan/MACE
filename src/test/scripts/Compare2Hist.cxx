#include "ROOT/RDataFrame.hxx"
#include "TCanvas.h"
#include "TFile.h"
#include "TH1.h"
#include "TPad.h"

#include <string>

void Compare2Hist() {
    //from sample file
    auto filePath1{"Sample.root"};
    auto histPath1{"SimMACE_signal/MCPSimHit/TrkID"};
    
    auto file1{new TFile(filePath1, "READ")};
    auto h1{static_cast<TH1D*>(file1->Get(histPath1))};
    //from test file
    auto filePath2{"SimMACE_signal_test.root"};
    auto treePath2{"G4Run0/MCPSimHit"};
    auto branchName{"TrkID"};

    ROOT::RDataFrame df0(treePath2, filePath2);
    auto df{df0};
    auto h2{df.Histo1D({"", "", h1->GetNbinsX(), h1->GetXaxis()->GetXmin(), h1->GetXaxis()->GetXmax()}, branchName)};

    h1->Scale(h1->Integral());
    h2->Scale(h2->Integral());

    TCanvas* c1 = new TCanvas("c1", "c1", 800, 600);
    TPad* pad1 = new TPad("pad1", "pad1", 0, 0.4, 1, 1.0);
    TPad* pad2 = new TPad("pad2", "pad2", 0, 0.0, 1, 0.4);

    pad1->SetBottomMargin(0.06);
    pad2->SetTopMargin(0.02);
    pad2->SetBottomMargin(0.2);

    pad1->Draw();
    pad2->Draw();

    h1->SetLineColor(kRed);
    h1->SetLineWidth(3);
    h2->SetLineColor(kBlue);
    h2->SetLineWidth(3);


    pad1->cd();
    h2->Draw();
    h1->Draw("same");

    pad2->cd();
    TH1D* residual{(TH1D*)h2->Clone("residual")};
    residual->Add(h1, -1.);
    residual->SetLineColor(kBlack);
    residual->Draw();
    c1->Update();
    c1->Draw();
}
