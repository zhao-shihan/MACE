#pragma once

#include "MACE/Env/Memory/Singleton.h++"

#include "G4UImessenger.hh"

#include "gsl/gsl"

#include <memory>

class G4UIcmdWithAnInteger;
class G4UIcommand;
class G4UIdirectory;

namespace MACE::inline Extension::Geant4X {

class MPIRunManager;

class MPIRunMessenger final : public Env::Memory::Singleton<MPIRunMessenger>,
                              public G4UImessenger {
    friend Env::Memory::SingletonInstantiator;

private:
    MPIRunMessenger();
    ~MPIRunMessenger();

public:
    auto Register(gsl::not_null<MPIRunManager*> mpirunManager) -> void { fMPIRunManager = mpirunManager; }

    auto SetNewValue(G4UIcommand* command, G4String value) -> void override;

private:
    MPIRunManager* fMPIRunManager;

    std::unique_ptr<G4UIdirectory> fDirectory;
    std::unique_ptr<G4UIcmdWithAnInteger> fPrintProgressModulo;
    std::unique_ptr<G4UIcommand> fPrintRunSummary;
};

} // namespace MACE::inline Extension::Geant4X
