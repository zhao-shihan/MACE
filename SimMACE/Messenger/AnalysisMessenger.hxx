#pragma once

#include "G4UImessenger.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithAString.hh"

#include "SimMACE/Global.hxx"

class MACE::SimMACE::Messenger::AnalysisMessenger final :
    public G4UImessenger {
public:
    static AnalysisMessenger* Instance();
private:
    AnalysisMessenger();
    ~AnalysisMessenger();
    AnalysisMessenger(const AnalysisMessenger&) = delete;
    AnalysisMessenger& operator=(const AnalysisMessenger&) = delete;

public:
    void Set(Analysis* pAnalysis) { fpAnalysis = pAnalysis; }

    void SetNewValue(G4UIcommand* command, G4String value) override;

private:
    Analysis* fpAnalysis;

    G4UIdirectory* fDirectory;
    G4UIcmdWithABool* fEnableCoincidenceOfCalorimeter;
    G4UIcmdWithABool* fEnableCoincidenceOfVertexDetector;
    G4UIcmdWithAString* fSetFileName;
};
