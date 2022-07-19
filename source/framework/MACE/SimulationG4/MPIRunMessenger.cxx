#include "MACE/SimulationG4/MPIRunManager.hxx"
#include "MACE/SimulationG4/MPIRunMessenger.hxx"

namespace MACE::SimulationG4 {

MPIRunMessenger::MPIRunMessenger() :
    Environment::Resource::Singleton<MPIRunMessenger>(),
    G4UImessenger(),
    fMPIRunManager(nullptr),
    fDirectory("/MPIRun/"),
    fSetPrintProgress("/MPIRun/SetPrintProgress", this) {

    fDirectory.SetGuidance("Specialized settings for MPIRunManager.");

    fSetPrintProgress.SetGuidance("Set display frequency of run progress. If set to 0, only run begin information will be displayed. Nothing will be displayed if set to <0. Classical /run/printprogress is disabled once this is set.");
    fSetPrintProgress.SetParameterName("modulo", false);
    fSetPrintProgress.AvailableForStates(G4State_PreInit, G4State_Idle);
}

void MPIRunMessenger::SetNewValue(G4UIcommand* command, G4String value) {
    if (command == std::addressof(fSetPrintProgress)) {
        fMPIRunManager->SetPrintProgress(fSetPrintProgress.GetNewIntValue(value));
        fMPIRunManager->G4RunManager::SetPrintProgress(-1);
    }
}

} // namespace MACE::SimulationG4
