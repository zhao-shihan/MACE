#pragma once

#include "MACE/Environment/Resource/Singleton.hxx"
#include "MACE/Utility/ObserverPtr.hxx"

#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIdirectory.hh"
#include "G4UImessenger.hh"

namespace MACE::SimMACE {

class Analysis;

namespace Messenger {

using Utility::ObserverPtr;

class AnalysisMessenger final : public Environment::Resource::Singleton<AnalysisMessenger>,
                                public G4UImessenger {
    friend class Environment::Resource::SingletonFactory;

private:
    AnalysisMessenger();
    ~AnalysisMessenger() = default;

public:
    void SetTo(ObserverPtr<Analysis> ana) { fAnalysis = ana; }

    void SetNewValue(G4UIcommand* command, G4String value) override;

private:
    ObserverPtr<Analysis> fAnalysis;

    G4UIdirectory fDirectory;
    G4UIcmdWithABool fEnableCoincidenceOfEMCal;
    G4UIcmdWithABool fEnableCoincidenceOfMCP;
    G4UIcmdWithAString fSetResultName;
};

} // namespace Messenger

} // namespace MACE::SimMACE
