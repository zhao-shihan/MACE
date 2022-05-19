#pragma once

#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UImessenger.hh"

namespace MACE::Simulation::SimTarget::Messenger {

class AnalysisMessenger final : public G4UImessenger {
public:
    static AnalysisMessenger& Instance();

private:
    AnalysisMessenger();
    ~AnalysisMessenger() noexcept = default;
    AnalysisMessenger(const AnalysisMessenger&) = delete;
    AnalysisMessenger& operator=(const AnalysisMessenger&) = delete;

public:
    void SetNewValue(G4UIcommand* command, G4String value) override;

private:
    G4UIdirectory fDirectory;
    G4UIcmdWithAString fSetResultName;
    G4UIcmdWithABool fEnableYieldAnalysis;
    G4UIcmdWithAString fSetDetectableRegion;
};

} // namespace MACE::Simulation::SimTarget::Messenger
