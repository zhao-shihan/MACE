#pragma once

#include "MACE/Extension/Geant4X/SingletonMessenger.h++"

#include <memory>

class G4UIcmdWithAnInteger;
class G4UIcommand;
class G4UIdirectory;

namespace MACE::inline Extension::Geant4X {

class MPIRunManager;

class MPIRunMessenger final : public Geant4X::SingletonMessenger<MPIRunMessenger,
                                                                 MPIRunManager> {
    friend Env::Memory::SingletonInstantiator;

private:
    MPIRunMessenger();
    ~MPIRunMessenger();

public:
    auto SetNewValue(G4UIcommand* command, G4String value) -> void override;

private:
    std::unique_ptr<G4UIdirectory> fDirectory;
    std::unique_ptr<G4UIcmdWithAnInteger> fPrintProgressModulo;
    std::unique_ptr<G4UIcommand> fPrintRunSummary;
};

} // namespace MACE::inline Extension::Geant4X
