#include "G4MPImanager.hh"

#include "Analysis.hh"
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
    AnalysisMessenger::Instance()->Set(this);
}

void Analysis::Open() {
    G4String fullFileName = fFileName;
    if (MPI::Is_initialized()) {
        std::stringstream ss;
        ss << fullFileName << "_rank" << G4MPImanager::GetManager()->GetRank() << ".root";
        ss >> fullFileName;
    }
    DataModel::Base::Manager::Open(fullFileName);
}

void Analysis::CreateAllBranchesFromCoincident() {
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
    CreateBranchFromTransientList<
        DataModel::kCalorimeter,
        DataModel::Hit::Persistency::Calorimeter>
        (fpCalorimeterHC->GetVector());
    CreateBranchFromTransientList<
        DataModel::kOrbitalDetector,
        DataModel::Hit::Persistency::OrbitalDetector>
        (fpOrbitalDetectorHC->GetVector());
    CreateBranchFromTransientList<
        DataModel::kSpectrometer,
        DataModel::Hit::Persistency::Spectrometer>
        (fpSpectrometerHC->GetVector());
}