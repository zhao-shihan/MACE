#pragma once

#include "G4UImessenger.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithAString.hh"

#include "SimMACE/Global.hxx"
#include "Utility/ObserverPtr.hxx"

class MACE::SimMACE::Messenger::AnalysisMessenger final :
    public G4UImessenger {
public:
    static AnalysisMessenger& Instance();

private:
    AnalysisMessenger();
    ~AnalysisMessenger() noexcept = default;
    AnalysisMessenger(const AnalysisMessenger&) = delete;
    AnalysisMessenger& operator=(const AnalysisMessenger&) = delete;

public:
    void Set(ObserverPtr<Analysis> analysis) { fAnalysis = analysis; }

    void SetNewValue(G4UIcommand* command, G4String value) override;

private:
    ObserverPtr<Analysis> fAnalysis = nullptr;

    G4UIdirectory fDirectory;
    G4UIcmdWithABool fEnableCoincidenceOfCalorimeter;
    G4UIcmdWithABool fEnableCoincidenceOfVertexDetector;
    G4UIcmdWithAString fSetFileName;
};
