#pragma once

#include "ObserverPtr.hxx"
#include "SimMACE/Global.hxx"

#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UImessenger.hh"

namespace MACE::Simulation::SimMACE::Messenger {

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
    G4UIcmdWithABool fEnableCoincidenceOfCalorimeter;
    G4UIcmdWithABool fEnableCoincidenceOfVertexDetector;
    G4UIcmdWithAString fSetResultName;
    G4UIcmdWithABool fMergeResult;
};

} // namespace MACE::Simulation::SimMACE::Messenger
