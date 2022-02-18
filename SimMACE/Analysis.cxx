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
    fDataHub(),
    fCalorimeterHitList(nullptr),
    fVertexDetectorHitList(nullptr),
    fSpectrometerHitList(nullptr),
    fTrueEventID(std::numeric_limits<G4int>::min()) {
    Messenger::AnalysisMessenger::Instance().Set(this);
}

void Analysis::Open(Option_t* option) {
    G4String fullFileName("");
    std::stringstream ss;
    bool isParallel = false;
    if (MPI::Is_initialized()) {
        if (G4MPImanager::GetManager()->GetActiveSize() > 1) {
            isParallel = true;
        }
    }
    if (isParallel) {
        ss << fFileName << "_rank" << G4MPImanager::GetManager()->GetRank() << ".root";
        ss >> fullFileName;
    } else {
        ss << fFileName << ".root";
        ss >> fullFileName;
    }
    fFile.reset(TFile::Open(fullFileName.c_str(), option));
}

void Analysis::Close(Option_t* option) {
    fFile->Close(option);
    fFile.reset();
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
