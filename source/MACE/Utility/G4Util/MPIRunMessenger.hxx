#pragma once

#include "MACE/Utility/ObserverPtr.hxx"

#include "G4UIcmdWithAnInteger.hh"
#include "G4UIdirectory.hh"
#include "G4UImessenger.hh"

namespace MACE::Utility::G4Util {

using Utility::ObserverPtr;

class MPIRunManager;

class MPIRunMessenger final : public G4UImessenger {
public:
    static MPIRunMessenger& Instance();

private:
    MPIRunMessenger();
    ~MPIRunMessenger() noexcept = default;
    MPIRunMessenger(const MPIRunMessenger&) = delete;
    MPIRunMessenger& operator=(const MPIRunMessenger&) = delete;

public:
    void SetTo(ObserverPtr<MPIRunManager> mpirunManager) { fMPIRunManager = mpirunManager; }

    void SetNewValue(G4UIcommand* command, G4String value) override;

private:
    ObserverPtr<MPIRunManager> fMPIRunManager = nullptr;

    G4UIdirectory fDirectory;
    G4UIcmdWithAnInteger fSetPrintProgress;
};

} // namespace MACE::Utility::G4Util
