#include "MACE/SimMACE/Analysis.hxx"
#include "MACE/SimMACE/Hit/CDCHit.hxx"
#include "MACE/SimMACE/Hit/EMCalHit.hxx"
#include "MACE/SimMACE/Hit/MCPHit.hxx"
#include "MACE/SimMACE/Messenger/AnalysisMessenger.hxx"
#include "MACE/SimMACE/Messenger/FieldMessenger.hxx"
#include "MACE/Utility/MPIUtil/MakeMPIFilePath.hxx"

#include "TFile.h"

namespace MACE::SimMACE {

Analysis::Analysis() :
    PassiveSingleton(),
    fResultPath("SimMACE_untitled"),
    fEnableCoincidenceOfEMCal(true),
    fEnableCoincidenceOfMCP(true),
    fDataHub(),
    fFile(),
    fEMCalHitTree(),
    fMCPHitTree(),
    fCDCHitTree(),
    fEMCalHitList(nullptr),
    fMCPHitList(nullptr),
    fCDCHitList(nullptr) {
    fDataHub.TreeNamePrefixFormat("G4Run{}_");
    AnalysisMessenger::Instance().AssignTo(this);
}

void Analysis::RunBegin(G4int runID, Option_t* option) {
    fFile = std::make_unique<TFile>(MPIUtil::MakeMPIFilePath(fResultPath, ".root").generic_string().c_str(),
                                    option,
                                    "",
                                    ROOT::RCompressionSetting::EDefaults::kUseSmallest);
    fEMCalHitTree = fDataHub.CreateTree<DataModel::EMCalSimHit>(runID);
    fMCPHitTree = fDataHub.CreateTree<DataModel::MCPSimHit>(runID);
    fCDCHitTree = fDataHub.CreateTree<DataModel::CDCSimHit>(runID);
}

void Analysis::EventEnd() {
    const auto emCalTriggered = not fEnableCoincidenceOfEMCal or fEMCalHitList->size() > 0;
    const auto mcpTriggered = not fEnableCoincidenceOfMCP or fMCPHitList->size() > 0;
    const auto cdcTriggered = fCDCHitList->size() > 0;
    // if coincident then write their data
    if (emCalTriggered and mcpTriggered and cdcTriggered) {
        fDataHub.FillTree(*fEMCalHitList, *fEMCalHitTree, true);
        fDataHub.FillTree(*fMCPHitList, *fMCPHitTree, true);
        fDataHub.FillTree(*fCDCHitList, *fCDCHitTree, true);
    }
}

void Analysis::RunEnd(Option_t* option) {
    fEMCalHitTree->Write();
    fMCPHitTree->Write();
    fCDCHitTree->Write();
    fFile->Close(option);
    fFile.reset();
}

} // namespace MACE::SimMACE
