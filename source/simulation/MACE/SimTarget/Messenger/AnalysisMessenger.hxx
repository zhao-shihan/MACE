#pragma once

#include "MACE/Environment/Memory/Singleton.hxx"
#include "MACE/Utility/ObserverPtr.hxx"

#include "G4UImessenger.hh"

#include <memory>

class G4UIcmdWithABool;
class G4UIcmdWithAString;
class G4UIdirectory;

namespace MACE::SimTarget {

class Analysis;

namespace Messenger {

using Utility::ObserverPtr;

class AnalysisMessenger final : public Environment::Memory::Singleton<AnalysisMessenger>,
                                public G4UImessenger {
    friend Environment::Memory::SingletonFactory;

private:
    AnalysisMessenger();
    ~AnalysisMessenger();

public:
    void SetTo(ObserverPtr<Analysis> ana) { fAnalysis = ana; }

    void SetNewValue(ObserverPtr<G4UIcommand> command, G4String value) override;

private:
    ObserverPtr<Analysis> fAnalysis;

    std::unique_ptr<G4UIdirectory> fDirectory;
    std::unique_ptr<G4UIcmdWithAString> fSetResultName;
    std::unique_ptr<G4UIcmdWithABool> fEnableYieldAnalysis;
};

} // namespace Messenger

} // namespace MACE::SimTarget
