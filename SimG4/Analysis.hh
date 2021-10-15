#pragma once

#include "SimG4/Global.hh"
#include "SimG4/Hit/CalorimeterHit.hh"
#include "SimG4/Hit/OrbitalDetectorHit.hh"
#include "SimG4/Hit/SpectrometerHit.hh"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wshadow" // suppress ridiculous warnings caused by TString: (const char* s) shadows CLHEP::s
#include "DataModel/PersistencyWriter.hh"
#pragma GCC diagnostic pop

class MACE::SimG4::Analysis final : private MACE::DataModel::PersistencyWriter {
    MACE_DATA_MODEL_NOT_ALLOW_TO_COPY(Analysis);
private:
    Analysis();
public:
    static Analysis* Instance();

    void SetFileName(const G4String& fileName) { fFileName = fileName; }
    const G4String& GetFileName() const { return fFileName; }
    void SetEnableCoincidenceOfCalorimeter(G4bool val) { fEnableCoincidenceOfCalorimeter = val; }

    void Open();
    using DataModel::PersistencyWriter::WriteTrees;
    using DataModel::PersistencyWriter::Close;

    void SetTrueEventID(G4int trueEventID) { SetNamePrefix(TString("Event") + trueEventID + '_'); }
    void SubmitCalorimeterHC(const std::vector<Hit::CalorimeterHit*>* hitList) { fpCalorimeterHitList = hitList; }
    void SubmitOrbitalDetectorHC(const std::vector<Hit::OrbitalDetectorHit*>* hitList) { fpOrbitalDetectorHitList = hitList; }
    void SubmitSpectrometerHC(const std::vector<Hit::SpectrometerHit*>* hitList) { fpSpectrometerHitList = hitList; }
    void RecordCoincidence();

private:
    G4String fFileName = "MACE_SimG4";
    G4bool   fEnableCoincidenceOfCalorimeter = true;

    const std::vector<Hit::CalorimeterHit*>* fpCalorimeterHitList;
    const std::vector<Hit::OrbitalDetectorHit*>* fpOrbitalDetectorHitList;
    const std::vector<Hit::SpectrometerHit*>* fpSpectrometerHitList;
};