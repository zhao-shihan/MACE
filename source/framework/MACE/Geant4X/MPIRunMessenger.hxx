#pragma once

#include "MACE/Env/Memory/Singleton.hxx"
#include "MACE/Utility/ObserverPtr.hxx"

#include "G4UImessenger.hh"

#include <memory>

class G4UIcmdWithAnInteger;
class G4UIdirectory;

namespace MACE::Geant4X {

class MPIRunManager;

using Utility::ObserverPtr;

class MPIRunMessenger final : public Env::Memory::Singleton<MPIRunMessenger>,
                              public G4UImessenger {
    friend Env::Memory::SingletonFactory;

private:
    MPIRunMessenger();
    ~MPIRunMessenger() = default;

public:
    void AssignTo(ObserverPtr<MPIRunManager> mpirunManager) { fMPIRunManager = mpirunManager; }

    void SetNewValue(G4UIcommand* command, G4String value) override;

private:
    ObserverPtr<MPIRunManager> fMPIRunManager;

    std::unique_ptr<G4UIdirectory> fDirectory;
    std::unique_ptr<G4UIcmdWithAnInteger> fSetPrintProgress;
};

} // namespace MACE::Geant4X
