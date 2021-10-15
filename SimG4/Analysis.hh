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
    void SubmitCalorimeterHC(const Hit::CollectionOfCalorimeter* const hc) { fpCalorimeterHC = hc; }
    void SubmitOrbitalDetectorHC(const Hit::CollectionOfOrbitalDetector* const hc) { fpOrbitalDetectorHC = hc; }
    void SubmitSpectrometerHC(const Hit::CollectionOfSpectrometer* const hc) { fpSpectrometerHC = hc; }
    void RecordCoincidence();

private:
    G4String fFileName = "MACE_SimG4";
    G4bool   fEnableCoincidenceOfCalorimeter = true;

    const Hit::CollectionOfCalorimeter* fpCalorimeterHC;
    const Hit::CollectionOfOrbitalDetector* fpOrbitalDetectorHC;
    const Hit::CollectionOfSpectrometer* fpSpectrometerHC;
};