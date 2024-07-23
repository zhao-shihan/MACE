#pragma once

#include "Mustard/Extension/Geant4X/Interface/SingletonMessenger.h++"

#include <memory>

class G4UIcmdWithABool;
class G4UIcmdWithAString;
class G4UIdirectory;

namespace MACE::SimDose {

class Analysis;

inline namespace Messenger {

class AnalysisMessenger final : public Mustard::Geant4X::SingletonMessenger<AnalysisMessenger,
                                                                            Analysis> {
    friend Mustard::Env::Memory::SingletonInstantiator;

private:
    AnalysisMessenger();
    ~AnalysisMessenger();

public:
    auto SetNewValue(G4UIcommand* command, G4String value) -> void override;

private:
    std::unique_ptr<G4UIdirectory> fDirectory;
};

} // namespace Messenger

} // namespace MACE::SimDose
