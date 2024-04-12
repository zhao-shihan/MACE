#pragma once

#include "MACE/Extension/Geant4X/SingletonMessenger.h++"

#include <memory>

class G4UIcmdWithADoubleAndUnit;
class G4UIdirectory;

namespace MACE::inline Simulation::inline Field {

class MMSField;

class MMSFieldMessenger final : public Geant4X::SingletonMessenger<MMSFieldMessenger> {
    friend Env::Memory::SingletonInstantiator;

private:
    MMSFieldMessenger();
    ~MMSFieldMessenger();

public:
    auto SetNewValue(G4UIcommand* command, G4String value) -> void override;

private:
    std::unique_ptr<G4UIdirectory> fDirectory;
    std::unique_ptr<G4UIcmdWithADoubleAndUnit> fMMSMagneticField;
};

} // namespace MACE::inline Simulation::inline Field
