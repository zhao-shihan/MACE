#pragma once

#include "MACE/Extension/Geant4X/SingletonMessenger.h++"

#include <memory>

class G4UIcmdWithADoubleAndUnit;
class G4UIdirectory;

namespace MACE::inline Simulation::inline Field {

class SolenoidB1Field;
class SolenoidB2Field;
class SolenoidS1Field;
class SolenoidS2Field;
class SolenoidS3Field;

class SolenoidFieldMessenger final : public Geant4X::SingletonMessenger<SolenoidFieldMessenger> {
    friend Env::Memory::SingletonInstantiator;

private:
    SolenoidFieldMessenger();
    ~SolenoidFieldMessenger();

public:
    auto SetNewValue(G4UIcommand* command, G4String value) -> void override;

private:
    std::unique_ptr<G4UIdirectory> fDirectory;
    std::unique_ptr<G4UIcmdWithADoubleAndUnit> fSolenoidMagneticField;
};

} // namespace MACE::inline Simulation::inline Field
