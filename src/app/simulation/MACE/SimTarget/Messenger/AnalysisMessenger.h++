#pragma once

#include "MACE/Env/Memory/Singleton.h++"

#include "G4UImessenger.hh"

#include "gsl/gsl"

#include <memory>

class G4UIcmdWithABool;
class G4UIcmdWithAString;
class G4UIdirectory;

namespace MACE::SimTarget {

class Analysis;

inline namespace Messenger {

class AnalysisMessenger final : public Env::Memory::Singleton<AnalysisMessenger>,
                                public G4UImessenger {
    friend Env::Memory::SingletonInstantiator;

private:
    AnalysisMessenger();
    ~AnalysisMessenger();

public:
    auto Register(gsl::not_null<Analysis*> ana) -> void { fAnalysis = ana; }

    auto SetNewValue(G4UIcommand* command, G4String value) -> void override;

private:
    Analysis* fAnalysis;

    std::unique_ptr<G4UIdirectory> fDirectory;
    std::unique_ptr<G4UIcmdWithAString> fResultPath;
    std::unique_ptr<G4UIcmdWithABool> fEnableYieldAnalysis;
};

} // namespace Messenger

} // namespace MACE::SimTarget
