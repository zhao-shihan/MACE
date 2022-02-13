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
    fpCalorimeterHitList(nullptr),
    fpVertexDetectorHitList(nullptr),
    fpSpectrometerHitList(nullptr),
    fTrueEventID(std::numeric_limits<G4int>::min()) {
    Messenger::AnalysisMessenger::Instance().Set(this);
}

void Analysis::Open() {
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
    DataModel::PersistencyWriter::Open(fullFileName);
}

void Analysis::WriteEvent() {
    const G4bool calorimeterTriggered = !(fEnableCoincidenceOfCalorimeter and fpCalorimeterHitList->empty());
    const G4bool vertexDetectorTriggered = !(fEnableCoincidenceOfVertexDetector and fpVertexDetectorHitList->empty());
    const G4bool spectrometerTriggered = !fpSpectrometerHitList->empty();
    if (calorimeterTriggered and vertexDetectorTriggered and spectrometerTriggered) {
        CreateTreeFromList<Hit::CalorimeterHit>(*fpCalorimeterHitList, fTrueEventID);
        CreateTreeFromList<Hit::VertexDetectorHit>(*fpVertexDetectorHitList, fTrueEventID);
        CreateTreeFromList<Hit::SpectrometerHit>(*fpSpectrometerHitList, fTrueEventID);
        WriteTrees();
    }
}