#include "ROOT/RDataFrame.hxx"
#include "TFile.h"
#include "TH1.h"
#include "TKey.h"
#include "TSystem.h"

#include <iostream>
#include <string>

const std::string dataTupleName{"MMSSimTrack"};

// int main()
auto TestMMSSimTrack(std::string moduleName, std::string testFileName, std::string sampleFileName) {
    // std::string moduleName{"SimMMS_em_flat"};
    // std::string testFileName{"SimMMS_em_flat1.root"};
    // std::string sampleFileName{"Sample.root"};
    gErrorIgnoreLevel = kError;
    ROOT::RDataFrame df0("G4Run0/" + dataTupleName, testFileName);
    auto sampleFile{new TFile(sampleFileName.data(), "READ")};
    if (!sampleFile) {
        std::cerr << "Err: Sample file not found: " << sampleFileName << std::endl;
        return 1;
    }
    auto sampleDir{static_cast<TDirectory*>(sampleFile->Get((moduleName + "/" + dataTupleName).data()))};
    if (!sampleDir) {
        std::cerr << "Err: data tuple not found: " << (moduleName + "/" + dataTupleName) << std::endl;
        return 1;
    }

    std::clog << "[Note] testing. Module: " << moduleName << "DataTuple: " << dataTupleName << std::endl;

    auto df{df0.Define("x0x", "x0[0]")
                .Define("x0y", "x0[1]")
                .Define("x0z", "x0[2]")
                .Define("c0x", "c0[0]")
                .Define("c0y", "c0[1]")
                .Define("p0x", "p0[0]")
                .Define("p0y", "p0[1]")
                .Define("p0z", "p0[2]")};

    auto histKeyList{sampleDir->GetListOfKeys()};
    std::clog << "Get " << histKeyList->GetEntries() << " entries from sample file." << std::endl;

    for (auto&& obj : *histKeyList) {
        auto key{(TKey*)obj};
        auto hist{static_cast<TH1D*>(key->ReadObj())};
        auto branchName{hist->GetName()};
        auto xMax{hist->GetXaxis()->GetXmax()};
        auto xMin{hist->GetXaxis()->GetXmin()};
        auto nBins{hist->GetNbinsX()};

        auto testHist{df.Histo1D({"", "", nBins, xMin, xMax}, branchName)};
        auto pValue{hist->Chi2Test(testHist.GetPtr())};
        std::clog << "[ ] Column " << branchName << " pValue: " << pValue << std::endl;
    }
    std::clog << "Test " << moduleName << " " << dataTupleName << " end." << std::endl;
    return 0;
}