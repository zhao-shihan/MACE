#include "MACE/Simulation/SD/MCPSD.h++"
#include "MACE/Simulation/SD/MCPSDMessenger.h++"

#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIdirectory.hh"

namespace MACE::inline Simulation::inline SD {

MCPSDMessenger::MCPSDMessenger() :
    SingletonMessenger{},
    fDirectory{},
    fIonizingEnergyDepositionThreshold{} {

    fDirectory = std::make_unique<G4UIdirectory>("/MACE/SD/MCP/");
    fDirectory->SetGuidance("MCP sensitive detector.");

    fIonizingEnergyDepositionThreshold = std::make_unique<G4UIcmdWithADoubleAndUnit>("/MACE/SD/MCP/IonizingEnergyDepositionThreshold", this);
    fIonizingEnergyDepositionThreshold->SetGuidance("Ionizing energy deposition threshold for a response.");
    fIonizingEnergyDepositionThreshold->SetParameterName("E", false);
    fIonizingEnergyDepositionThreshold->SetUnitCategory("Energy");
    fIonizingEnergyDepositionThreshold->SetRange("E >= 0");
    fIonizingEnergyDepositionThreshold->AvailableForStates(G4State_Idle);
}

MCPSDMessenger::~MCPSDMessenger() = default;

auto MCPSDMessenger::SetNewValue(G4UIcommand* command, G4String value) -> void {
    if (command == fIonizingEnergyDepositionThreshold.get()) {
        Deliver<MCPSD>([&](auto&& r) {
            r.IonizingEnergyDepositionThreshold(fIonizingEnergyDepositionThreshold->GetNewDoubleValue(value));
        });
    }
}

} // namespace MACE::inline Simulation::inline SD
