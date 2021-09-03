#pragma once

#include "G4UImessenger.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithAString.hh"

#include "SimG4Global.hh"

class MACE::SimG4::AnalysisMessenger : public G4UImessenger {
public:
    static AnalysisMessenger* Instance();
private:
    AnalysisMessenger();
    ~AnalysisMessenger();
    AnalysisMessenger(const AnalysisMessenger&) = delete;
    AnalysisMessenger& operator=(const AnalysisMessenger&) = delete;

public:
    void SetAnalysis(Analysis* pAnalysis) { fpAnalysis = pAnalysis; }

    void SetNewValue(G4UIcommand* command, G4String value) override;

private:
    Analysis* fpAnalysis;
    
    G4UIdirectory* fDirectory;
    G4UIcmdWithADoubleAndUnit* fSetCalorimeterWindowWidth;
    G4UIcmdWithADoubleAndUnit* fSetSpectrometerWindowWidth;
    G4UIcmdWithABool* fEnableCoincidenceOfCalorimeter;
    G4UIcmdWithAString* fSetFileName;
};
