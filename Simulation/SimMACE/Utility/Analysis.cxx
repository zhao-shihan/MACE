#include "G4MPImanager.hh"

#include "SimMACE/Utility/Analysis.hxx"
#include "SimMACE/Messenger/AnalysisMessenger.hxx"
#include "SimMACE/Messenger/FieldMessenger.hxx"

using namespace MACE::SimMACE::Utility;

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
    fSpectrometerHitTree(nullptr),
    fCalorimeterHitList(nullptr),
    fVertexDetectorHitList(nullptr),
    fSpectrometerHitList(nullptr) {
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
    if (fMPIFileTools == nullptr) {
        G4ExceptionDescription description("There is nothing to merge!");
        G4Exception("MACE::SimMACE::Utility::Analysis::Merge(G4bool)",
            "MACE_SimMACE_Analysis_W0", JustWarning, description);
        return -1;
    }
    return fMPIFileTools->MergeRootFiles(forced);
}

void Analysis::WriteEvent(G4int repetitionID) {
    if (repetitionID != fRepetitionIDOfLastG4Event) { // means a new repetition or the first repetition
        // last repetition had already come to the end, write its data. If first, skipped inside.
        WriteTrees();
        // create trees for new repetition
        fCalorimeterHitTree = fDataHub.CreateTree<DataModel::CalorimeterSimHit>(repetitionID);
        fVertexDetectorHitTree = fDataHub.CreateTree<DataModel::VertexDetectorSimHit>(repetitionID);
        fSpectrometerHitTree = fDataHub.CreateTree<DataModel::SpectrometerSimHit>(repetitionID);
    }

    fDataHub.FillTree<DataModel::CalorimeterSimHit>(*fCalorimeterHitList, *fCalorimeterHitTree);
    fDataHub.FillTree<DataModel::VertexDetectorSimHit>(*fVertexDetectorHitList, *fVertexDetectorHitTree);
    fDataHub.FillTree<DataModel::SpectrometerSimHit>(*fSpectrometerHitList, *fSpectrometerHitTree);

    // dont forget to update repID!
    fRepetitionIDOfLastG4Event = repetitionID;
}

void Analysis::WriteTrees() {
    if (fCalorimeterHitTree == nullptr or fVertexDetectorHitTree == nullptr or fSpectrometerHitTree == nullptr) { return; }
    const auto calorimeterTriggered = !fEnableCoincidenceOfCalorimeter or fCalorimeterHitTree->GetEntries() != 0;
    const auto vertexDetectorTriggered = !fEnableCoincidenceOfVertexDetector or fVertexDetectorHitTree->GetEntries() != 0;
    const auto spectrometerTriggered = fSpectrometerHitTree->GetEntries() != 0;
    // if all coincident then write their data
    if (calorimeterTriggered and vertexDetectorTriggered and spectrometerTriggered) {
        fCalorimeterHitTree->Write();
        fVertexDetectorHitTree->Write();
        fSpectrometerHitTree->Write();
    }
}
