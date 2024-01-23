#include "MACE/Extension/Geant4X/MPIRunManager.h++"
#include "MACE/Extension/Geant4X/MPIRunMessenger.h++"

#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcommand.hh"
#include "G4UIdirectory.hh"

namespace MACE::inline Extension::Geant4X {

MPIRunMessenger::MPIRunMessenger() :
    SingletonMessenger{},
    fDirectory{},
    fPrintProgressModulo{},
    fPrintRunSummary{} {

    fDirectory = std::make_unique<G4UIdirectory>("/MPIRun/");
    fDirectory->SetGuidance("Specialized settings for MPIRunManager.");

    fPrintProgressModulo = std::make_unique<G4UIcmdWithAnInteger>("/MPIRun/PrintProgressModulo", this);
    fPrintProgressModulo->SetGuidance("Set display frequency of run progress. If set to 0, only run begin information will be displayed. Nothing will be displayed if set to <0. Classical /run/printprogress is disabled once this is set.");
    fPrintProgressModulo->SetParameterName("modulo", false);
    fPrintProgressModulo->AvailableForStates(G4State_PreInit, G4State_Idle);

    fPrintRunSummary = std::make_unique<G4UIcommand>("/MPIRun/PrintRunSummary", this);
    fPrintRunSummary->SetGuidance("Print MPI run performace summary.");
    fPrintRunSummary->AvailableForStates(G4State_Idle);
}

MPIRunMessenger::~MPIRunMessenger() = default;

auto MPIRunMessenger::SetNewValue(G4UIcommand* command, G4String value) -> void {
    if (command == fPrintProgressModulo.get()) {
        Deliver<MPIRunManager>([&](auto&& r) {
            r.PrintProgressModulo(fPrintProgressModulo->GetNewIntValue(value));
        });
    } else if (command == fPrintRunSummary.get()) {
        Deliver<MPIRunManager>([&](auto&& r) {
            r.PrintRunSummary();
        });
    }
}

} // namespace MACE::inline Extension::Geant4X
