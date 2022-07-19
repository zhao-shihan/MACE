#pragma once

#include "MACE/Environment/Resource/Singleton.hxx"
#include "MACE/Utility/ObserverPtr.hxx"

#include "G4UIcmdWithAnInteger.hh"
#include "G4UIdirectory.hh"
#include "G4UImessenger.hh"

namespace MACE::Utility::G4Util {

class MPIRunManager;

using Utility::ObserverPtr;

class MPIRunMessenger final : public Environment::Resource::Singleton<MPIRunMessenger>,
                              public G4UImessenger {
    friend Environment::Resource::SingletonFactory;

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

} // namespace MACE::Utility::G4Util
