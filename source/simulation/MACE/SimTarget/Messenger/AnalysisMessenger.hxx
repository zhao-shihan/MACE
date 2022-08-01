#pragma once

#include "MACE/Environment/Memory/Singleton.hxx"
#include "MACE/Utility/ObserverPtr.hxx"

#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIdirectory.hh"
#include "G4UImessenger.hh"

namespace MACE::SimTarget {

class Analysis;

namespace Messenger {

using Utility::ObserverPtr;

class AnalysisMessenger final : public Environment::Memory::Singleton<AnalysisMessenger>,
                                public G4UImessenger {
    friend Environment::Memory::SingletonFactory;

private:
    AnalysisMessenger();
    ~AnalysisMessenger() = default;

public:
    void SetTo(ObserverPtr<Analysis> ana) { fAnalysis = ana; }

    void SetNewValue(G4UIcommand* command, G4String value) override;

private:
    ObserverPtr<Analysis> fAnalysis;

    G4UIdirectory fDirectory;
    G4UIcmdWithAString fSetResultName;
    G4UIcmdWithABool fEnableYieldAnalysis;
    G4UIcmdWithAString fSetDetectableRegion;
};

} // namespace Messenger

} // namespace MACE::SimTarget
