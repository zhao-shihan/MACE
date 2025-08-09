#include "ROOT/RDataFrame.hxx"
#include "TBranch.h"
#include "TDirectory.h"
#include "TFile.h"
#include "TH1.h"
#include "TTree.h"
#include "TTreeReader.h"
#include "TTreeReaderArray.h"
#include "TTreeReaderValue.h"

#include "muc/array"

#include "gsl/gsl"

#include <array>
#include <iostream>
#include <ranges>
#include <string>
#include <string_view>
#include <unordered_set>

#define nBins_value_type 100

/*
src file:
Sim[SOME_MODULE].root
        ...        |
      (TDirectory): G4Run0/
            |
            (TTree): SimPrimaryVertex
                     SimDecayVertex
                     [SOME_MODULE]SimHit
                     ...
                                |
                                (TBranch): EvtID(int)
                                           PDGID(int)
                                           ...
                                           t(double)
                                           x(double)
                                           ...
                                           TrkID(vector<int>)
                                           nOptPho(vector<int>)
                                           ...
                                           [SOME_BRANCH](vector<double>)
                                           ...
                                           CreatProc(string)

target merged file:
Sample.root
        |
        (TDirectory): Sim[SOMEMODULE]
        ...
                        |
                        (TDirectory): SimPrimaryVertex
                                      SimDecayVertex
                                      [SOME_MODULE]SimHit
                                      ...
                                                    |
                                                    (TH1[SUITABLE_TYPE]): EvtID(int)
                                                                          PDGID(int)
                                                                          ...
                                                                          t(double)
                                                                          x(double)
                                                                          ...
                                                                          TrkID(vector<int>)
                                                                          nOptPho(vector<int>)
                                                                          ...
                                                                          [SOME_BRANCH](vector<double>)
                                                                          ...
                                                                          CreatProc(string)



*/
namespace name {
using namespace std::string_view_literals;
using namespace ROOT::Internal;

class FillProcess {

public:
    FillProcess(std::string moduleName,
                std::string srcFileName,
                std::string srcTreeName,
                std::string targetFileName = "Sample.root");

    FillProcess() = delete;
    FillProcess(const FillProcess&) = delete;
    FillProcess(FillProcess&&) = delete;
    FillProcess& operator=(const FillProcess&) = delete;

    ~FillProcess() {
        if (fSrcFile)
            fSrcFile->Delete();
        if (fTargetFile)
            fTargetFile->Delete();
        if (fModuleDir)
            fModuleDir->Delete();
        if (fFillDir)
            fFillDir->Delete();
    }

    void Fill();

private:
    std::string fModuleName;
    std::string fSrcFileName;
    std::string fSrcTreeName;
    std::string fTargetFileName;
    gsl::owner<TFile*> fSrcFile{nullptr};
    gsl::owner<TFile*> fTargetFile{nullptr};
    gsl::owner<TDirectory*> fModuleDir{nullptr};
    gsl::owner<TDirectory*> fFillDir{nullptr};
};

FillProcess::FillProcess(std::string moduleName,
                         std::string srcFileName,
                         std::string srcTreeName,
                         std::string targetFileName) :
    fModuleName{std::move(moduleName)},
    fSrcFileName{std::move(srcFileName)},
    fSrcTreeName{std::move(srcTreeName)},
    fTargetFileName{std::move(targetFileName)},
    fSrcFile{TFile::Open(fSrcFileName.c_str(), "READ")},
    fTargetFile{TFile::Open(fTargetFileName.c_str(), "UPDATE")} {

    if (!fSrcFile || fSrcFile->IsZombie()) {
        throw std::runtime_error("Error: Failed to open source file: " + fSrcFileName);
    }

    if (!fTargetFile || fTargetFile->IsZombie()) {
        throw std::runtime_error("Error: Failed to open target file: " + fTargetFileName);
    }

    if (fSrcTreeName.empty()) {
        throw std::runtime_error("Error: Empty tree name");
    }

    fModuleDir = fTargetFile->GetDirectory(fModuleName.c_str());
    if (!fModuleDir) {
        fModuleDir = fTargetFile->mkdir(fModuleName.c_str());
    }

    fFillDir = fModuleDir->GetDirectory(fSrcTreeName.c_str());
    if (!fFillDir) {
        fFillDir = fModuleDir->mkdir(fSrcTreeName.c_str());
    }
}

void FillProcess::Fill() {

    auto srcTree = dynamic_cast<TTree*>(fSrcFile->Get(fSrcTreeName.c_str()));
    if (!srcTree) {
        std::cerr << "Error: Could not find tree " << fSrcTreeName << " in source file\n";
        return;
    }
    auto srcTreeReader{TTreeReader(srcTree)};
    auto df{ROOT::RDataFrame(fSrcTreeName.c_str(), fSrcFileName.c_str())};

    const std::unordered_set skipBranches = {"EvtID"sv, "HitID"sv, "Good"sv, "PDGID"sv, "CreatProc"sv, "nOptPho"sv, "nOptPhoOnEachSiPM"sv, "SecPDGID"sv};
    const std::unordered_set arrayfBranches = {"x"sv, "x0"sv, "p"sv, "p0"sv, "c0"sv};

    fFillDir->cd();
    auto srcBranchList{srcTree->GetListOfBranches()};
    for (auto* branch : TRangeDynCast<TBranch>(srcBranchList)) {

        if (!branch) {
            std::cout << "Warning: A branch is null." << std::endl;
            continue;
        }

        std::string_view branchName{branch->GetName()};
        if (skipBranches.count(branchName)) {
            std::cout << "Note: Skip this branch named " << branchName << "--Not interested." << std::endl;
            continue;
        }

        auto intReader{TTreeReaderArray<Int_t>(srcTreeReader, branchName.data())};
        auto floatReader{TTreeReaderArray<float_t>(srcTreeReader, branchName.data())};
        auto shortReader{TTreeReaderArray<Short_t>(srcTreeReader, branchName.data())};
        auto boolReader{TTreeReaderArray<Bool_t>(srcTreeReader, branchName.data())};

        bool isIntBranch{intReader.GetSetupStatus() == TTreeReaderValueBase::ESetupStatus::kSetupMatch};
        bool isFloatBranch{floatReader.GetSetupStatus() == TTreeReaderValueBase::ESetupStatus::kSetupMatch};
        bool isShortBranch{shortReader.GetSetupStatus() == TTreeReaderValueBase::ESetupStatus::kSetupMatch};
        bool isboolBranch{boolReader.GetSetupStatus() == TTreeReaderValueBase::ESetupStatus::kSetupMatch};
        bool isArrayfBranch{arrayfBranches.count(branchName)};

        if (isIntBranch or isFloatBranch or isShortBranch) {
            std::cout << "Get value_type branch named " << branchName << std::endl;
            auto xMin{*df.Min(branchName.data())};
            auto xMax{*df.Max(branchName.data())};
            auto hist = df.Histo1D({branchName.data(), branchName.data(), nBins_value_type, xMin, xMax}, branchName);
            hist->Write();
        }
        if (isboolBranch) {
            std::cout << "Get bool branch named " << branchName << std::endl;
            auto hist = df.Histo1D({branchName.data(), branchName.data(), 2, 0, 1}, branchName);
            hist->Write();
        }
        if (isArrayfBranch) {
            // TODO
        }
    }
}

} // namespace name

//
// auto FillTree(TFile* srcFile, TFile* targetFile, char* treeName, TDirectory* moduleDir) -> void {
// auto srcTreePath{("G4Run0" + std::string(treeName)).c_str()};
// auto srcTree{(TTree*)srcFile->Get(srcTreePath)};
// auto targetDir{moduleDir->mkdir(treeName)};
// }