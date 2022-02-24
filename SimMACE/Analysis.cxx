#include "G4MPImanager.hh"

#include "SimMACE/Analysis.hxx"
#include "SimMACE/Messenger/AnalysisMessenger.hxx"
#include "SimMACE/Messenger/FieldMessenger.hxx"

using namespace MACE::SimMACE;

Analysis& Analysis::Instance() {
    static Analysis instance;
    return instance;
}

Analysis::Analysis() :
    fFile(nullptr),
    fFileTools4MPI(nullptr),
    fTrueEventID(std::numeric_limits<G4int>::min()),
    fDataHub(),
    fCalorimeterHitList(nullptr),
    fVertexDetectorHitList(nullptr),
    fSpectrometerHitList(nullptr) {
    Messenger::AnalysisMessenger::Instance();
    FileTools4MPI::SetOutStream(G4cout);
}

void Analysis::Open(Option_t* option) {
    if (MPI::Is_initialized()) {
        fFileTools4MPI = std::make_unique<FileTools4MPI>(fResultName, ".root", *G4MPImanager::GetManager()->GetComm());
    } else {
        fFileTools4MPI = std::make_unique<FileTools4MPI>(fResultName, ".root");
    }
    fFile.reset(TFile::Open(fFileTools4MPI->GetFilePath().c_str(), option));
}

void Analysis::Close(Option_t* option) {
    fFile->Close(option);
    // must delete the file object otherwise segmentation violation.
    fFile.reset();
}

int Analysis::Merge(G4bool forced) {
    if (fFileTools4MPI == nullptr) {
        G4ExceptionDescription description("There is nothing to merge!");
        G4Exception("MACE::SimMACE::Analysis::Merge(G4bool)",
            "MACE_SimMACE_Analysis_W0", JustWarning, description);
        return -1;
    }
    return fFileTools4MPI->MergeRootFiles(forced);
}

void Analysis::WriteEvent() {
    const G4bool calorimeterTriggered = !(fEnableCoincidenceOfCalorimeter and fCalorimeterHitList->empty());
    const G4bool vertexDetectorTriggered = !(fEnableCoincidenceOfVertexDetector and fVertexDetectorHitList->empty());
    const G4bool spectrometerTriggered = !fSpectrometerHitList->empty();
    if (calorimeterTriggered and vertexDetectorTriggered and spectrometerTriggered) {
        fDataHub.CreateTree(*fCalorimeterHitList, fTrueEventID)->Write();
        fDataHub.CreateTree(*fVertexDetectorHitList, fTrueEventID)->Write();
        fDataHub.CreateTree(*fSpectrometerHitList, fTrueEventID)->Write();
    }
}
