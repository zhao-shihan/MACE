#pragma once

#include "MACE/Env/Memory/Singleton.hxx"
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

class AnalysisMessenger final : public Env::Memory::Singleton<AnalysisMessenger>,
                                public G4UImessenger {
    friend Env::Memory::SingletonFactory;

private:
    AnalysisMessenger();
    ~AnalysisMessenger();

public:
    void AssignTo(ObserverPtr<Analysis> ana) { fAnalysis = ana; }

    void SetNewValue(ObserverPtr<G4UIcommand> command, G4String value) override;

private:
    ObserverPtr<Analysis> fAnalysis;

    std::unique_ptr<G4UIdirectory> fDirectory;
    std::unique_ptr<G4UIcmdWithAString> fSetResultPath;
    std::unique_ptr<G4UIcmdWithABool> fEnableYieldAnalysis;
};

} // namespace Messenger

} // namespace MACE::SimTarget
