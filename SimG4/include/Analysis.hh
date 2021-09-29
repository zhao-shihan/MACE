#pragma once

#include "g4analysis.hh"
#include "G4Positron.hh"

#include "SimG4Global.hh"
#include "detector/hit/CalorimeterHit.hh"
#include "detector/hit/OrbitalDetectorHit.hh"
#include "detector/hit/SpectrometerHit.hh"

class MACE::SimG4::Analysis {
public:
    static Analysis* Instance();
    ~Analysis();
private:
    static Analysis* instance;
    Analysis();
    Analysis(const Analysis&) = delete;
    Analysis& operator=(const Analysis&) = delete;

public:
    void Initialize();
    void Open() const;

    void SetPluseID(G4int pluseID) { fPluseID = pluseID; }
    void SubmitCalorimeterHC(const Hit::CalorimeterHitsCollection* const hc) { fpCalorimeterHC = hc; }
    void SubmitOrbitalDetectorHC(const Hit::OrbitalDetectorHitsCollection* const hc) { fpOrbitalDetectorHC = hc; }
    void SubmitSpectrometerHC(const Hit::SpectrometerHitsCollection* const hc) { fpSpectrometerHC = hc; }
    void Fill() const;

    void WriteAndClose() const;

    void SetEnableCoincidenceOfCalorimeter(G4bool val) { fEnableCoincidenceOfCalorimeter = val; }
    void SetFileName(const G4String& fileName) { fFileName = fileName; }

private:
    G4ToolsAnalysisManager* fpG4Analysis;
    const Hit::CalorimeterHitsCollection* fpCalorimeterHC;
    const Hit::OrbitalDetectorHitsCollection* fpOrbitalDetectorHC;
    const Hit::SpectrometerHitsCollection* fpSpectrometerHC;

    G4bool   fEnableCoincidenceOfCalorimeter = true;

    G4int    fPluseID = 0;

    G4String fFileName = "MACE_SimG4";
};