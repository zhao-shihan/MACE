#include "ROOT/RDataFrame.hxx"
#include "TFile.h"
#include "TH1.h"
#include "TKey.h"
#include "TSystem.h"

#include <iostream>
#include <string>

const std::string dataTupleName{"VetoSimHit"};
const void Judge(double pValue) {
    const std::string boldBlue = "\033[1;34m";
    const std::string boldGreen = "\033[1;32m";
    const std::string boldRed = "\033[1;31m";
    const std::string boldOrange = "\033[1;33m";
    const std::string reset = "\033[0m";

    std::clog << "(#) ";
    if (pValue < 0.003) {
        std::cout << boldRed << "FAIL" << reset << " (p = " << pValue << ")" << std::endl;
    } else if (pValue < 0.05) {
        std::cout << boldOrange << "SUSPICIOUS" << reset << " (p = " << pValue << ")" << std::endl;
    } else if (pValue != 0) {
        std::cout << boldGreen << "PASS" << reset << " (p = " << pValue << ")" << std::endl;
    } else {
        std::cout << boldBlue << "IDENTICAL" << reset << " (p = " << pValue << ")" << std::endl;
    }
}

// int main()
auto TestVetoSimHit(std::string moduleName, std::string testFileName, std::string sampleFileName) {
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

    auto histKeyList{sampleDir->GetListOfKeys()};
    std::clog << "Get " << histKeyList->GetEntries() << " entries from sample file." << std::endl;
    int idx{};
    for (auto&& obj : *histKeyList) {
        auto key{(TKey*)obj};
        auto hist{static_cast<TH1D*>(key->ReadObj())};
        auto branchName{hist->GetName()};
        auto xMax{hist->GetXaxis()->GetXmax()};
        auto xMin{hist->GetXaxis()->GetXmin()};
        auto nBins{hist->GetNbinsX()};

        auto testHist{df.Histo1D({"", "", nBins, xMin, xMax}, branchName)};
        std::clog << "[" << ++idx << "] " << " Column " << branchName << std::endl;
        auto pValue{hist->Chi2Test(testHist.GetPtr(), "P")};
        Judge(pValue);
        std::cout << "\n";
    }
    std::clog << "Test " << moduleName << " " << dataTupleName << " end." << std::endl;
    return 0;
}