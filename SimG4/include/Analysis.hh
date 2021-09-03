#pragma once

#include "g4analysis.hh"

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
    void SubmitCalorimeterHC(const Hit::CalorimeterHitsCollection* const hc) { fpCalorimeterHC = hc; }
    void SubmitOrbitalDetectorHC(const Hit::OrbitalDetectorHitsCollection* const hc) { fpOrbitalDetectorHC = hc; }
    void SubmitSpectrometerHC(const Hit::SpectrometerHitsCollection* const hc) { fpSpectrometerHC = hc; }
    void DoCoincidenceAnalysisAndFill() const;
    void WriteAndClose() const;

    void SetCalorimeterWindowWidth(G4double val) { fCalorimeterWindowWidth = val; }
    void SetMeanTOF(G4double val) { fMeanTOF = val; }
    void SetSpectrometerWindowWidth(G4double val) { fSpectrometerWindowWidth = val; }
    void SetEnableCoincidenceOfCalorimeter(G4bool val) { fEnableCoincidenceOfCalorimeter = val; }
    void SetFileName(const G4String& fileName) { fFileName = fileName; }

private:
    void FillOrbitalDetectorHit(const Hit::OrbitalDetectorHit* const hit) const;
    void FillCalorimeterHits(const std::vector<Hit::CalorimeterHit*>::const_iterator hitBegin, const std::vector<Hit::CalorimeterHit*>::const_iterator hitEnd) const;
    void FillSpectrometerHits(const std::vector<Hit::SpectrometerHit*>::const_iterator hitBegin, const std::vector<Hit::SpectrometerHit*>::const_iterator hitEnd) const;

private:
    G4ToolsAnalysisManager* fpG4Analysis;
    const Hit::CalorimeterHitsCollection* fpCalorimeterHC;
    const Hit::OrbitalDetectorHitsCollection* fpOrbitalDetectorHC;
    const Hit::SpectrometerHitsCollection* fpSpectrometerHC;

    G4double fCalorimeterWindowWidth = 2 * ns;
    G4double fMeanTOF = 2985 * mm / (c_light * sqrt(2 * 2 * keV / (511 * keV)));
    G4double fSpectrometerWindowWidth = 8 * ns;

    G4bool fEnableCoincidenceOfCalorimeter = true;

    G4String fFileName = "MACE_SimG4";
};