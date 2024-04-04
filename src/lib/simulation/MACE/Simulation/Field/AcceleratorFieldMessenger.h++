#pragma once

#include "MACE/Extension/Geant4X/SingletonMessenger.h++"

#include <memory>

class G4UIcmdWithADoubleAndUnit;
class G4UIdirectory;

namespace MACE::inline Simulation::inline Field {

class AcceleratorField;

class AcceleratorFieldMessenger final : public Geant4X::SingletonMessenger<AcceleratorFieldMessenger> {
    friend Env::Memory::SingletonInstantiator;

private:
    AcceleratorFieldMessenger();
    ~AcceleratorFieldMessenger();

public:
    auto SetNewValue(G4UIcommand* command, G4String value) -> void override;

private:
    std::unique_ptr<G4UIdirectory> fDirectory;
    std::unique_ptr<G4UIcmdWithADoubleAndUnit> fAcceleratePotential;
};

} // namespace MACE::inline Simulation::inline Field
