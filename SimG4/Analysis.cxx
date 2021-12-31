#include "G4MPImanager.hh"

#include "SimG4/Analysis.hxx"
#include "SimG4/Messenger/AnalysisMessenger.hxx"
#include "SimG4/Messenger/FieldMessenger.hxx"

using namespace MACE::SimG4;

Analysis* Analysis::Instance() {
    static Analysis instance;
    return &instance;
}

Analysis::Analysis() :
    fpCalorimeterHitList(nullptr),
    fpOrbitalDetectorHitList(nullptr),
    fpSpectrometerHitList(nullptr) {
    Messenger::AnalysisMessenger::Instance()->Set(this);
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
    const G4bool calorimeterTriggered = !(fEnableCoincidenceOfCalorimeter && fpCalorimeterHitList->empty());
    const G4bool orbitalDetectorTriggered = !(fEnableCoincidenceOfOrbitalDetector && fpOrbitalDetectorHitList->empty());
    const G4bool spectrometerTriggered = !fpSpectrometerHitList->empty();
    if (calorimeterTriggered && orbitalDetectorTriggered && spectrometerTriggered) {
        CreateTreeFromList(fpCalorimeterHitList);
        CreateTreeFromList(fpOrbitalDetectorHitList);
        CreateTreeFromList(fpSpectrometerHitList);
        WriteTrees();
    }
}