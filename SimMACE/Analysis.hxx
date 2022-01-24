#pragma once

#include "SimMACE/Global.hxx"
#include "SimMACE/Hit/CalorimeterHit.hxx"
#include "SimMACE/Hit/OrbitalDetectorHit.hxx"
#include "SimMACE/Hit/SpectrometerHit.hxx"

#include "DataModel/PersistencyWriter.hxx"

class MACE::SimMACE::Analysis final : private MACE::DataModel::PersistencyWriter {
    Analysis(const Analysis&) = delete;
    Analysis& operator=(const Analysis&) = delete;
private:
    Analysis();
public:
    static Analysis* Instance();

    void SetFileName(const G4String& fileName) { fFileName = fileName; }
    const G4String& GetFileName() const { return fFileName; }
    void SetEnableCoincidenceOfCalorimeter(G4bool val) { fEnableCoincidenceOfCalorimeter = val; }
    void SetEnableCoincidenceOfOrbitalDetector(G4bool val) { fEnableCoincidenceOfOrbitalDetector = val; }

    void Open();
    using DataModel::PersistencyWriter::Close;

    void SetTrueEventID(G4int trueEventID) { SetTreeIndex(trueEventID); }
    void SubmitCalorimeterHC(const std::vector<Hit::CalorimeterHit*>* hitList) { fpCalorimeterHitList = hitList; }
    void SubmitOrbitalDetectorHC(const std::vector<Hit::OrbitalDetectorHit*>* hitList) { fpOrbitalDetectorHitList = hitList; }
    void SubmitSpectrometerHC(const std::vector<Hit::SpectrometerHit*>* hitList) { fpSpectrometerHitList = hitList; }
    void WriteEvent();

private:
    G4String fFileName = "MACE_SimMACE";
    G4bool   fEnableCoincidenceOfCalorimeter = true;
    G4bool   fEnableCoincidenceOfOrbitalDetector = true;

    const std::vector<Hit::CalorimeterHit*>* fpCalorimeterHitList;
    const std::vector<Hit::OrbitalDetectorHit*>* fpOrbitalDetectorHitList;
    const std::vector<Hit::SpectrometerHit*>* fpSpectrometerHitList;
};