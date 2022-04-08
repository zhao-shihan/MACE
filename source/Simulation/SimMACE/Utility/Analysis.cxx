#include "Simulation/SimMACE/Messenger/AnalysisMessenger.hxx"
#include "Simulation/SimMACE/Messenger/FieldMessenger.hxx"
#include "Simulation/SimMACE/Utility/Analysis.hxx"

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
    fCalorimeterHitTree(nullptr),
    fVertexDetectorHitTree(nullptr),
    fCDCHitTree(nullptr),
    fCalorimeterHitList(nullptr),
    fVertexDetectorHitList(nullptr),
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
        fCalorimeterHitTree = fDataHub.CreateTree<CalorimeterSimHit>(repetitionID);
        fVertexDetectorHitTree = fDataHub.CreateTree<VertexDetectorSimHit>(repetitionID);
        fCDCHitTree = fDataHub.CreateTree<CDCSimHit>(repetitionID);
    }

    fDataHub.FillTree<CalorimeterSimHit>(*fCalorimeterHitList, *fCalorimeterHitTree, true);
    fDataHub.FillTree<VertexDetectorSimHit>(*fVertexDetectorHitList, *fVertexDetectorHitTree, true);
    fDataHub.FillTree<CDCSimHit>(*fCDCHitList, *fCDCHitTree, true);

    // dont forget to update repID!
    fRepetitionIDOfLastG4Event = repetitionID;
}

void Analysis::WriteTrees() {
    if (fCalorimeterHitTree == nullptr or fVertexDetectorHitTree == nullptr or fCDCHitTree == nullptr) { return; }
    const auto calorimeterTriggered = !fEnableCoincidenceOfCalorimeter or fCalorimeterHitTree->GetEntries() != 0;
    const auto vertexDetectorTriggered = !fEnableCoincidenceOfVertexDetector or fVertexDetectorHitTree->GetEntries() != 0;
    const auto spectrometerTriggered = fCDCHitTree->GetEntries() != 0;
    // if all coincident then write their data
    if (calorimeterTriggered and vertexDetectorTriggered and spectrometerTriggered) {
        fCalorimeterHitTree->Write();
        fVertexDetectorHitTree->Write();
        fCDCHitTree->Write();
    }
}

} // namespace MACE::Simulation::SimMACE::Utility
