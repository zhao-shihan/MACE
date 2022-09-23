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
    FreeSingleton(),
    fFile(nullptr),
    fResultPath("untitled_SimMACE"),
    fEnableCoincidenceOfEMCal(true),
    fEnableCoincidenceOfMCP(true),
    fDataHub(),
    fRepetitionIdOfLastG4Event(std::numeric_limits<decltype(fRepetitionIdOfLastG4Event)>::max()),
    fEMCalHitTree(nullptr),
    fMCPHitTree(nullptr),
    fCDCHitTree(nullptr),
    fEMCalHitList(nullptr),
    fMCPHitList(nullptr),
    fCDCHitList(nullptr) {
    Messenger::AnalysisMessenger::Instance().AssignTo(this);
    fDataHub.TreeNamePrefixFormat("Rep{}_");
}

void Analysis::Open(Option_t* option) {
    fFile = std::make_unique<TFile>(
        Utility::MPIUtil::MakeMPIFilePath(fResultPath, ".root").generic_string().c_str(),
        option);
}

void Analysis::Close(Option_t* option) {
    WriteTrees();
    fFile->Close(option);
    // must delete the file object otherwise segmentation violation.
    fFile.reset();
}

void Analysis::WriteEvent(G4int repetitionId) {
    using namespace Core::DataModel::SimHit;

    if (repetitionId != fRepetitionIdOfLastG4Event) { // means a new repetition or the first repetition
        // last repetition had already come to the end, write its data. If first, skipped inside.
        WriteTrees();
        // create trees for new repetition
        fEMCalHitTree = fDataHub.CreateTree<EMCalSimHit>(repetitionId);
        fMCPHitTree = fDataHub.CreateTree<MCPSimHit>(repetitionId);
        fCDCHitTree = fDataHub.CreateTree<CDCSimHit>(repetitionId);
    }

    fDataHub.FillTree(*fEMCalHitList, *fEMCalHitTree, true);
    fDataHub.FillTree(*fMCPHitList, *fMCPHitTree, true);
    fDataHub.FillTree(*fCDCHitList, *fCDCHitTree, true);

    // dont forget to update repId!
    fRepetitionIdOfLastG4Event = repetitionId;
}

void Analysis::WriteTrees() {
    if (fEMCalHitTree == nullptr or fMCPHitTree == nullptr or fCDCHitTree == nullptr) { return; }
    const auto emCalTriggered = not fEnableCoincidenceOfEMCal or fEMCalHitTree->GetEntries() != 0;
    const auto mcpTriggered = not fEnableCoincidenceOfMCP or fMCPHitTree->GetEntries() != 0;
    const auto cdcTriggered = fCDCHitTree->GetEntries() != 0;
    // if all coincident then write their data
    if (emCalTriggered and mcpTriggered and cdcTriggered) {
        fEMCalHitTree->Write();
        fMCPHitTree->Write();
        fCDCHitTree->Write();
    }
}

} // namespace MACE::SimMACE
