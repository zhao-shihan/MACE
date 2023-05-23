#include "MACE/Extension/Geant4X/MPIRunManager.hxx"
#include "MACE/Extension/Geant4X/MPIRunMessenger.hxx"

#include "G4UIcmdWithAnInteger.hh"
#include "G4UIdirectory.hh"

namespace MACE::inline Extension::Geant4X {

MPIRunMessenger::MPIRunMessenger() :
    Singleton(),
    G4UImessenger(),
    fMPIRunManager(nullptr),
    fDirectory(nullptr),
    fPrintProgressModulo(nullptr) {

    fDirectory = std::make_unique<G4UIdirectory>("/MPIRun/");
    fDirectory->SetGuidance("Specialized settings for MPIRunManager.");

    fPrintProgressModulo = std::make_unique<G4UIcmdWithAnInteger>("/MPIRun/PrintProgressModulo", this);
    fPrintProgressModulo->SetGuidance("Set display frequency of run progress. If set to 0, only run begin information will be displayed. Nothing will be displayed if set to <0. Classical /run/printprogress is disabled once this is set.");
    fPrintProgressModulo->SetParameterName("modulo", false);
    fPrintProgressModulo->AvailableForStates(G4State_PreInit, G4State_Idle);
}

MPIRunMessenger::~MPIRunMessenger() = default;

void MPIRunMessenger::SetNewValue(G4UIcommand* command, G4String value) {
    if (command == fPrintProgressModulo.get()) {
        fMPIRunManager->PrintProgressModulo(fPrintProgressModulo->GetNewIntValue(value));
    }
}

} // namespace MACE::inline Extension::Geant4X
