#include "MACE/Simulation/SimMACE/Analysis.hxx"
#include "MACE/Simulation/SimMACE/Messenger/AnalysisMessenger.hxx"
#include "MACE/Simulation/SimMACE/Messenger/FieldMessenger.hxx"
#include "MACE/Utility/MPIUtil/MakeMPIFilePath.hxx"

namespace MACE::Simulation::SimMACE {

Analysis& Analysis::Instance() {
    static Analysis instance;
    return instance;
}

Analysis::Analysis() :
    fFile(nullptr),
    fDataHub(),
    fRepetitionIDOfLastG4Event(std::numeric_limits<decltype(fRepetitionIDOfLastG4Event)>::max()),
    fEMCalHitTree(nullptr),
    fMCPHitTree(nullptr),
    fCDCHitTree(nullptr),
    fEMCalHitList(nullptr),
    fMCPHitList(nullptr),
    fCDCHitList(nullptr) {
    Messenger::AnalysisMessenger::Instance();
    fDataHub.SetTreeNamePrefixFormat("Rep#_");
}

void Analysis::Open(Option_t* option) {
    std::string filePath;
    filePath = MACE::Utility::MPIUtil::MakeMPIFilePath(fResultName, ".root");
    fFile = std::make_unique<TFile>(filePath.c_str(), option);
}

void Analysis::Close(Option_t* option) {
    WriteTrees();
    fFile->Close(option);
    // must delete the file object otherwise segmentation violation.
    fFile.reset();
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

} // namespace MACE::Simulation::SimMACE
