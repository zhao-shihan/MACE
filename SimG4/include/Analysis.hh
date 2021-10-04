#pragma once

#include "SimG4Global.hh"
#include "detector/hit/Calorimeter.hh"
#include "detector/hit/OrbitalDetector.hh"
#include "detector/hit/Spectrometer.hh"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wshadow" // suppress ridiculous warnings caused by TString: (const char* s) shadows CLHEP::s
#include "hit/Manager.hh"
#pragma GCC diagnostic pop

class MACE::SimG4::Analysis final : private MACE::DataModel::Hit::Manager {
    MACE_DATA_MODEL_NOT_ALLOW_TO_COPY(Analysis);
private:
    Analysis();
public:
    static Analysis* Instance();

    void SetFileName(const G4String& fileName) { fFileName = fileName; }
    void SetEnableCoincidenceOfCalorimeter(G4bool val) { fEnableCoincidenceOfCalorimeter = val; }

    void Open();
    using DataModel::Hit::Manager::Write;
    using DataModel::Hit::Manager::Close;

    void SetTrueEventID(G4int trueEventID) { SetBranchTitle(TString("Event") + trueEventID); }
    void SubmitCalorimeterHC(const Hit::CollectionOfCalorimeter* const hc) { fpCalorimeterHC = hc; }
    void SubmitOrbitalDetectorHC(const Hit::CollectionOfOrbitalDetector* const hc) { fpOrbitalDetectorHC = hc; }
    void SubmitSpectrometerHC(const Hit::CollectionOfSpectrometer* const hc) { fpSpectrometerHC = hc; }
    void CreateAllBranchesFromCoincident();

private:
    G4String fFileName = "MACE_SimG4";
    G4bool   fEnableCoincidenceOfCalorimeter = true;

    const Hit::CollectionOfCalorimeter* fpCalorimeterHC;
    const Hit::CollectionOfOrbitalDetector* fpOrbitalDetectorHC;
    const Hit::CollectionOfSpectrometer* fpSpectrometerHC;
};