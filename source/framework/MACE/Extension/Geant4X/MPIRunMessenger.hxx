#pragma once

#include "MACE/Env/Memory/Singleton.hxx"

#include "G4UImessenger.hh"

#include "gsl/gsl"

#include <memory>

class G4UIcmdWithAnInteger;
class G4UIdirectory;

namespace MACE::inline Extension::Geant4X {

class MPIRunManager;

class MPIRunMessenger final : public Env::Memory::Singleton<MPIRunMessenger>,
                              public G4UImessenger {
    friend Env::Memory::SingletonFactory;

private:
    MPIRunMessenger();
    ~MPIRunMessenger() = default;

public:
    void AssignTo(gsl::not_null<MPIRunManager*> mpirunManager) { fMPIRunManager = mpirunManager; }

    void SetNewValue(G4UIcommand* command, G4String value) override;

private:
    MPIRunManager* fMPIRunManager;

    std::unique_ptr<G4UIdirectory> fDirectory;
    std::unique_ptr<G4UIcmdWithAnInteger> fSetPrintProgress;
};

} // namespace MACE::inline Extension::Geant4X
