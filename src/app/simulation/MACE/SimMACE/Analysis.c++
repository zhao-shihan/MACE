#include "MACE/SimMACE/Analysis.h++"
#include "MACE/SimMACE/Hit/CDCHit.h++"
#include "MACE/SimMACE/Hit/EMCHit.h++"
#include "MACE/SimMACE/Hit/MCPHit.h++"
#include "MACE/SimMACE/Messenger/AnalysisMessenger.h++"
#include "MACE/Utility/MPIUtil/MakeMPIFilePath.h++"

#include "TFile.h"

namespace MACE::SimMACE {

Analysis::Analysis() :
    PassiveSingleton{},
    fFilePath{"SimMACE_untitled"},
    fFileOption{"UPDATE"},
    fEnableCoincidenceOfEMC{true},
    fEnableCoincidenceOfMCP{true},
    fDataHub{},
    fFile{},
    fEMCHitTree{},
    fMCPHitTree{},
    fCDCHitTree{},
    fEMCHitList{nullptr},
    fMCPHitList{nullptr},
    fCDCHitList{nullptr}{
    fDataHub.TreeNamePrefixFormat("G4Run{}_");
    AnalysisMessenger::Instance().AssignTo(this);
}

void Analysis::RunBegin(G4int runID) {
    fFile = std::make_unique<TFile>(MPIUtil::MakeMPIFilePath(fFilePath, ".root").generic_string().c_str(),
                                    fFileOption.c_str(),
                                    "",
                                    ROOT::RCompressionSetting::EDefaults::kUseGeneralPurpose);
    fEMCHitTree = fDataHub.CreateTree<DataModel::EMCSimHit>(runID);
    fMCPHitTree = fDataHub.CreateTree<DataModel::MCPSimHit>(runID);
    fCDCHitTree = fDataHub.CreateTree<DataModel::CDCSimHit>(runID);
}

void Analysis::EventEnd() {
    const auto emcTriggered = not fEnableCoincidenceOfEMC or fEMCHitList->size() > 0;
    const auto mcpTriggered = not fEnableCoincidenceOfMCP or fMCPHitList->size() > 0;
    const auto cdcTriggered = fCDCHitList->size() > 0;
    // if coincident then write their data
    if (emcTriggered and mcpTriggered and cdcTriggered) {
        fDataHub.FillTree(*fEMCHitList, *fEMCHitTree, true);
        fDataHub.FillTree(*fMCPHitList, *fMCPHitTree, true);
        fDataHub.FillTree(*fCDCHitList, *fCDCHitTree, true);
    }
}

void Analysis::RunEnd(Option_t* option) {
    fEMCHitTree->Write();
    fMCPHitTree->Write();
    fCDCHitTree->Write();
    fFile->Close(option);
    fFile.reset();
}

} // namespace MACE::SimMACE
