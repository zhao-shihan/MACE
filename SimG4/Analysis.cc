#include "G4MPImanager.hh"

#include "SimG4/Analysis.hh"
#include "SimG4/Messenger/AnalysisMessenger.hh"
#include "SimG4/Messenger/FieldMessenger.hh"

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
    if (MPI::Is_initialized()) {
        ss << fFileName << "_rank" << G4MPImanager::GetManager()->GetRank() << ".root";
        ss >> fullFileName;
    } else {
        ss << fFileName << ".root";
        ss >> fullFileName;
    }
    DataModel::PersistencyWriter::Open(fullFileName);
}

void Analysis::RecordCoincidence() {
    if (fEnableCoincidenceOfCalorimeter) {
        if (fpCalorimeterHitList->empty() ||
            fpOrbitalDetectorHitList->empty() ||
            fpSpectrometerHitList->empty()) {
            return;
        }
    } else {
        if (fpOrbitalDetectorHitList->empty() ||
            fpSpectrometerHitList->empty()) {
            return;
        }
    }
    CreateTreeFromList(fpCalorimeterHitList);
    CreateTreeFromList(fpOrbitalDetectorHitList);
    CreateTreeFromList(fpSpectrometerHitList);
    WriteTrees();
}