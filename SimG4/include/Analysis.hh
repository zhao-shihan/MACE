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

    void Open(const G4String& fileName) const;

    void SubmitCalorimeterHC(const Hit::CalorimeterHitsCollection* const hc) { fpCalorimeterHC = hc; }
    void SubmitOrbitalDetectorHC(const Hit::OrbitalDetectorHitsCollection* const hc) { fpOrbitalDetectorHC = hc; }
    void SubmitSpectrometerHC(const Hit::SpectrometerHitsCollection* const hc) { fpSpectrometerHC = hc; }

    void DoCoincidenceAnalysisAndFill() const;

    void WriteAndClose() const;

private:
    void FillOrbitalDetectorHit(const Hit::OrbitalDetectorHit* const hit) const;
    void FillCalorimeterHits(const std::vector<Hit::CalorimeterHit*>::const_iterator hitBegin, const std::vector<Hit::CalorimeterHit*>::const_iterator hitEnd) const;
    void FillSpectrometerHits(const std::vector<Hit::SpectrometerHit*>::const_iterator hitBegin, const std::vector<Hit::SpectrometerHit*>::const_iterator hitEnd) const;

private:
    G4ToolsAnalysisManager* fpAnalysis;
    const Hit::CalorimeterHitsCollection* fpCalorimeterHC;
    const Hit::OrbitalDetectorHitsCollection* fpOrbitalDetectorHC;
    const Hit::SpectrometerHitsCollection* fpSpectrometerHC;
};