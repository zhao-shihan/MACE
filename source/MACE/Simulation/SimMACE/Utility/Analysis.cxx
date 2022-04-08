#include "MACE/Simulation/SimMACE/Messenger/AnalysisMessenger.hxx"
#include "MACE/Simulation/SimMACE/Messenger/FieldMessenger.hxx"
#include "MACE/Simulation/SimMACE/Utility/Analysis.hxx"

#include "G4MPImanager.hh"

namespace MACE::Simulation::SimMACE::Utility {

using Messenger::AnalysisMessenger;

Analysis& Analysis::Instance() {
    static Analysis instance;
    return instance;
}

Analysis::Analysis() :
    fFile(nullptr),
    fMPIFileTools(nullptr),
    fDataHub(),
    fRepetitionIDOfLastG4Event(std::numeric_limits<decltype(fRepetitionIDOfLastG4Event)>::max()),
    fEMCalHitTree(nullptr),
    fMCPHitTree(nullptr),
    fCDCHitTree(nullptr),
    fEMCalHitList(nullptr),
    fMCPHitList(nullptr),
    fCDCHitList(nullptr) {
    AnalysisMessenger::Instance();
    MPIFileTools::SetOutStream(G4cout);
    fDataHub.SetPrefixFormatOfTreeName("Rep#_");
}

void Analysis::Open(Option_t* option) {
    if (MPI::Is_initialized()) {
        fMPIFileTools = std::make_unique<MPIFileTools>(fResultName, ".root", *G4MPImanager::GetManager()->GetComm());
    } else {
        fMPIFileTools = std::make_unique<MPIFileTools>(fResultName, ".root");
    }
    fFile.reset(TFile::Open(fMPIFileTools->GetFilePath().c_str(), option));
}

void Analysis::Close(Option_t* option) {
    WriteTrees();
    fFile->Close(option);
    // must delete the file object otherwise segmentation violation.
    fFile.reset();
}

int Analysis::Merge(G4bool forced) {
    if (fMPIFileTools) {
        return fMPIFileTools->MergeRootFiles(forced);
    } else {
        return MPIFileTools::MergeRootFilesViaFilesMap(fResultName, forced);
    }
}

void Analysis::WriteEvent(G4int repetitionID) {
    using namespace Core::DataModel::SimHit;

    if (repetitionID != fRepetitionIDOfLastG4Event) { // means a new repetition or the first repetition
        // last repetition had already come to the end, write its data. If first, skipped inside.
        WriteTrees();
        // create trees for new repetition
        fEMCalHitTree = fDataHub.CreateTree<EMCalSimHit>(repetitionID);
        fMCPHitTree = fDataHub.CreateTree<MCPSimHit>(repetitionID);
        fCDCHitTree = fDataHub.CreateTree<CDCSimHit>(repetitionID);
    }

    fDataHub.FillTree<EMCalSimHit>(*fEMCalHitList, *fEMCalHitTree, true);
    fDataHub.FillTree<MCPSimHit>(*fMCPHitList, *fMCPHitTree, true);
    fDataHub.FillTree<CDCSimHit>(*fCDCHitList, *fCDCHitTree, true);

    // dont forget to update repID!
    fRepetitionIDOfLastG4Event = repetitionID;
}

void Analysis::WriteTrees() {
    if (fEMCalHitTree == nullptr or fMCPHitTree == nullptr or fCDCHitTree == nullptr) { return; }
    const auto emCalTriggered = !fEnableCoincidenceOfEMCal or fEMCalHitTree->GetEntries() != 0;
    const auto mcpTriggered = !fEnableCoincidenceOfMCP or fMCPHitTree->GetEntries() != 0;
    const auto cdcTriggered = fCDCHitTree->GetEntries() != 0;
    // if all coincident then write their data
    if (emCalTriggered and mcpTriggered and cdcTriggered) {
        fEMCalHitTree->Write();
        fMCPHitTree->Write();
        fCDCHitTree->Write();
    }
}

} // namespace MACE::Simulation::SimMACE::Utility
