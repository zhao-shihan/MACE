#pragma once

#include "MACE/Environment/Memory/Singleton.hxx"
#include "MACE/Utility/ObserverPtr.hxx"

#include "G4UIcmdWithAnInteger.hh"
#include "G4UIdirectory.hh"
#include "G4UImessenger.hh"

namespace MACE::Geant4X {

class MPIRunManager;

using Utility::ObserverPtr;

class MPIRunMessenger final : public Environment::Memory::Singleton<MPIRunMessenger>,
                              public G4UImessenger {
    friend Environment::Memory::SingletonFactory;

private:
    MPIRunMessenger();
    ~MPIRunMessenger() = default;

public:
    void SetTo(ObserverPtr<MPIRunManager> mpirunManager) { fMPIRunManager = mpirunManager; }

    void SetNewValue(G4UIcommand* command, G4String value) override;

private:
    ObserverPtr<MPIRunManager> fMPIRunManager;

    G4UIdirectory fDirectory;
    G4UIcmdWithAnInteger fSetPrintProgress;
};

} // namespace MACE::SimulationG4
