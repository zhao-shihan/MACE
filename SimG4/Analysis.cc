#include "G4MPImanager.hh"

#include "SimG4/Analysis.hh"
#include "messenger/AnalysisMessenger.hh"
#include "messenger/FieldMessenger.hh"

using namespace MACE::SimG4;

Analysis* Analysis::Instance() {
    static Analysis instance;
    return &instance;
}

Analysis::Analysis() :
    fpCalorimeterHC(nullptr),
    fpOrbitalDetectorHC(nullptr),
    fpSpectrometerHC(nullptr) {
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
        if (fpCalorimeterHC->entries() == 0 ||
            fpOrbitalDetectorHC->entries() == 0 ||
            fpSpectrometerHC->entries() == 0) {
            return;
        }
    } else {
        if (fpOrbitalDetectorHC->entries() == 0 ||
            fpSpectrometerHC->entries() == 0) {
            return;
        }
    }
    CreateTree(fpCalorimeterHC->GetVector());
    CreateTree(fpOrbitalDetectorHC->GetVector());
    CreateTree(fpSpectrometerHC->GetVector());
    WriteTrees();
}