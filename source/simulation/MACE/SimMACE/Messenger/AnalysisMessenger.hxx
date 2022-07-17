#pragma once

#include "MACE/Utility/ObserverPtr.hxx"

#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIdirectory.hh"
#include "G4UImessenger.hh"

namespace MACE::SimMACE::Messenger {

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
    G4UIcmdWithABool fEnableCoincidenceOfEMCal;
    G4UIcmdWithABool fEnableCoincidenceOfMCP;
    G4UIcmdWithAString fSetResultName;
};

} // namespace MACE::SimMACE::Messenger
