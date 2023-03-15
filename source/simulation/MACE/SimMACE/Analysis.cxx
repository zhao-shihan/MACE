#include "MACE/SimMACE/Analysis.hxx"
#include "MACE/SimMACE/Hit/CDCHit.hxx"
#include "MACE/SimMACE/Hit/EMCalHit.hxx"
#include "MACE/SimMACE/Hit/MCPHit.hxx"
#include "MACE/SimMACE/Messenger/AnalysisMessenger.hxx"
#include "MACE/SimMACE/Messenger/FieldMessenger.hxx"
#include "MACE/Utility/MPIUtil/MakeMPIFilePath.hxx"

#include "ROOT/RDataFrame.hxx"
#include "TFile.h"

namespace MACE::SimMACE {

Analysis::Analysis() :
    FreeSingleton(),
    fFile(nullptr),
    fResultPath("SimMACE_untitled"),
    fEnableCoincidenceOfEMCal(true),
    fEnableCoincidenceOfMCP(true),
    fDataHub(),
    fEMCalHitList(nullptr),
    fMCPHitList(nullptr),
    fCDCHitList(nullptr) {
    Messenger::AnalysisMessenger::Instance().AssignTo(this);
    fDataHub.TreeNamePrefixFormat("Evt{}_");
}

void Analysis::Open(Option_t* option) {
    fFile = new TFile(MPIUtil::MakeMPIFilePath(fResultPath, ".root").generic_string().c_str(),
                      option,
                      "",
                      ROOT::RCompressionSetting::EDefaults::kUseSmallest);
}

void Analysis::Close(Option_t* option) {
    fFile->Close(option);
    delete fFile;
}

void Analysis::WriteEvent(G4int eventID) {
    using namespace DataModel::SimHit;

    // create and fill trees
    const auto emCalHitTree = fDataHub.CreateTree<EMCalSimHit>(eventID);
    const auto mcpHitTree = fDataHub.CreateTree<MCPSimHit>(eventID);
    const auto cdcHitTree = fDataHub.CreateTree<CDCSimHit>(eventID);
    fDataHub.FillTree(*fEMCalHitList, *emCalHitTree, true);
    fDataHub.FillTree(*fMCPHitList, *mcpHitTree, true);
    fDataHub.FillTree(*fCDCHitList, *cdcHitTree, true);

    const auto emCalTriggered = not fEnableCoincidenceOfEMCal or emCalHitTree->GetEntries() > 0;
    const auto mcpTriggered = not fEnableCoincidenceOfMCP or mcpHitTree->GetEntries() > 0;
    const auto cdcTriggered = cdcHitTree->GetEntries() > 0;
    // if coincident then write their data
    if (emCalTriggered and mcpTriggered and cdcTriggered) {
        emCalHitTree->Write();
        mcpHitTree->Write();
        cdcHitTree->Write();
    }
}

} // namespace MACE::SimMACE
