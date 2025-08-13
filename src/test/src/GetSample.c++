#include "ROOT/RDataFrame.hxx"
#include "ROOT/RVec.hxx"
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
// int GetSample(std::string moduleName, std::string srcFileName, std::string srcTreeName, std::string targetFileName) {
//     auto aProcess{FillProcess(moduleName, srcFileName, srcTreeName, targetFileName)};
//     aProcess.Fill();
//     return 0;
// }

using namespace std::string_view_literals;
using namespace ROOT::Internal;

int main(int argc, char* argv[]) {
    std::string moduleName{argv[1]};
    std::string srcFileName{argv[2]};
    std::string srcTreeName{argv[3]};
    std::string targetFileName{argv[4]};
    auto srcFile{new TFile(srcFileName.c_str(), "READ")};
    auto targetFile{new TFile(targetFileName.c_str(), "UPDATE")};

    if (!srcFile || srcFile->IsZombie()) {
        throw std::runtime_error("Error: Failed to open source file: " + srcFileName);
    }

    if (!targetFile || targetFile->IsZombie()) {
        throw std::runtime_error("Error: Failed to open target file: " + targetFileName);
    }

    if (srcTreeName.empty()) {
        throw std::runtime_error("Error: Empty tree name");
    }

    auto moduleDir{targetFile->GetDirectory(moduleName.c_str())};
    if (!moduleDir) {
        moduleDir = targetFile->mkdir(moduleName.c_str());
    }

    auto fillDir{moduleDir->GetDirectory(srcTreeName.c_str())};
    if (!fillDir) {
        fillDir = moduleDir->mkdir(srcTreeName.c_str());
    }
    auto srcTree = dynamic_cast<TTree*>(srcFile->Get(srcTreeName.c_str()));
    if (!srcTree) {
        std::cerr << "Error: Could not find tree " << srcTreeName << " in source file\n";
        return 1;
    }
    auto srcTreeReader{TTreeReader(srcTree)};
    auto df{ROOT::RDataFrame(srcTreeName.c_str(), srcFileName.c_str())};

    const std::unordered_set skipBranches = {"EvtID"sv, "HitID"sv, "Good"sv, "PDGID"sv, "CreatProc"sv, "nOptPho"sv, "nOptPhoOnEachSiPM"sv, "SecPDGID"sv};
    const std::unordered_set arrayfBranches = {"x"sv, "x0"sv, "p"sv, "p0"sv, "c0"sv};

    fillDir->cd();
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
        bool isArrayfBranch{static_cast<bool>(arrayfBranches.count(branchName))};

        std::cout << isIntBranch << " " << isFloatBranch << " " << isShortBranch << " " << isboolBranch << " " << isArrayfBranch << " " << std::endl;
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
            std::cout << "Get array branch named " << branchName << std::endl;
            auto arraySize{df.Take<ROOT::VecOps::RVec<float>>(branchName).GetValue().at(0).size()};
            auto hists{std::vector<TH1F>()};
            auto arrayComponents{std::vector<std::vector<float>>(arraySize)};
            df.Foreach([&](const ROOT::RVec<float>& aArray) {
                for (size_t i{}; i < arraySize; ++i) {
                    arrayComponents[i].emplace_back(aArray[i]);
                }
            },
                       {branchName.data()});

            for (size_t i{}; i < arraySize; ++i) {
                auto thisHistName{(std::string(branchName) + std::to_string(i)).c_str()};
                hists.emplace_back(TH1F(thisHistName, thisHistName, nBins_value_type, arrayComponents.at(i).data()));
            }
            for (auto aHist : hists) {
                aHist.Write();
            }
        }
    }
    if (srcFile)
        srcFile->Close();
    if (targetFile)
        targetFile->Close();
    // if (moduleDir)
    //     moduleDir->Delete();
    // if (fillDir)
    //     fillDir->Delete();
    return 0;
}

//
// auto FillTree(TFile* srcFile, TFile* targetFile, char* treeName, TDirectory* moduleDir) -> void {
// auto srcTreePath{("G4Run0" + std::string(treeName)).c_str()};
// auto srcTree{(TTree*)srcFile->Get(srcTreePath)};
// auto targetDir{moduleDir->mkdir(treeName)};
// }