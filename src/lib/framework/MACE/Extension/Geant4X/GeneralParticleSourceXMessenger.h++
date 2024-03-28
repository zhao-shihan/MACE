#pragma once

#include "MACE/Extension/Geant4X/SingletonMessenger.h++"

#include <memory>

class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithAnInteger;
class G4UIdirectory;

namespace MACE::inline Extension::Geant4X {

class GeneralParticleSourceX;

class GeneralParticleSourceXMessenger final : public Geant4X::SingletonMessenger<GeneralParticleSourceXMessenger,
                                                                                 GeneralParticleSourceX> {
    friend Env::Memory::SingletonInstantiator;

private:
    GeneralParticleSourceXMessenger();
    ~GeneralParticleSourceXMessenger();

public:
    auto SetNewValue(G4UIcommand* command, G4String value) -> void override;

private:
    std::unique_ptr<G4UIdirectory> fDirectory;
    std::unique_ptr<G4UIcmdWithAnInteger> fNVertex;
    std::unique_ptr<G4UIcmdWithADoubleAndUnit> fPulseWidth;
};

} // namespace MACE::inline Extension::Geant4X
