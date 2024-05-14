#pragma once

#include "MACE/Extension/Geant4X/SingletonMessenger.h++"

#include <memory>

class G4UIcmdWithADouble;
class G4UIcmdWithoutParameter;
class G4UIdirectory;

namespace MACE::inline Simulation::inline Physics {

class MuoniumTwoBodyDecayPhysics;

class MuoniumTwoBodyDecayPhysicsMessenger final : public Geant4X::SingletonMessenger<MuoniumTwoBodyDecayPhysicsMessenger,
                                                                                     MuoniumTwoBodyDecayPhysics> {
    friend Env::Memory::SingletonInstantiator;

private:
    MuoniumTwoBodyDecayPhysicsMessenger();
    ~MuoniumTwoBodyDecayPhysicsMessenger();

public:
    auto SetNewValue(G4UIcommand* command, G4String value) -> void override;

private:
    std::unique_ptr<G4UIdirectory> fDirectory;
    std::unique_ptr<G4UIcmdWithADouble> fAnnihilationBR;
    std::unique_ptr<G4UIcmdWithADouble> fTwoBodyDecayBR;
    std::unique_ptr<G4UIcmdWithoutParameter> fUpdateDecayBR;
};

} // namespace MACE::inline Simulation::inline Physics
