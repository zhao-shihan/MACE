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
    G4String fullFileName("");
    std::stringstream ss;
    if (MPI::Is_initialized()) {
        ss << fFileName << "_rank" << G4MPImanager::GetManager()->GetRank() << ".root";
        ss >> fullFileName;
    } else {
        ss << fFileName << ".root";
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
    Persistify<
        DataModel::kCalorimeter,
        DataModel::Hit::Persistency::Calorimeter>
        (fpCalorimeterHC->GetVector());
    Persistify<
        DataModel::kOrbitalDetector,
        DataModel::Hit::Persistency::OrbitalDetector>
        (fpOrbitalDetectorHC->GetVector());
    Persistify<
        DataModel::kSpectrometer,
        DataModel::Hit::Persistency::Spectrometer>
        (fpSpectrometerHC->GetVector());
}