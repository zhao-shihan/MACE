#include "MACE/PhaseI/SimMACEPhaseI/SD/MRPCSD.h++"
#include "MACE/PhaseI/SimMACEPhaseI/SD/MRPCSDMessenger.h++"

#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIdirectory.hh"

namespace MACE::PhaseI::SimMACEPhaseI::inline SD {

MRPCSDMessenger::MRPCSDMessenger() :
    SingletonMessenger{},
    fDirectory{},
    fIonizingEnergyDepositionThreshold{} {

    fDirectory = std::make_unique<G4UIdirectory>("/MACE/SD/MRPC/");
    fDirectory->SetGuidance("MRPC sensitive detector.");

    fIonizingEnergyDepositionThreshold = std::make_unique<G4UIcmdWithADoubleAndUnit>("/MACE/SD/MRPC/IonizingEnergyDepositionThreshold", this);
    fIonizingEnergyDepositionThreshold->SetGuidance("Ionizing energy deposition threshold for a response.");
    fIonizingEnergyDepositionThreshold->SetParameterName("E", false);
    fIonizingEnergyDepositionThreshold->SetUnitCategory("Energy");
    fIonizingEnergyDepositionThreshold->SetRange("E >= 0");
    fIonizingEnergyDepositionThreshold->AvailableForStates(G4State_Idle);
}

MRPCSDMessenger::~MRPCSDMessenger() = default;

auto MRPCSDMessenger::SetNewValue(G4UIcommand* command, G4String value) -> void {
    if (command == fIonizingEnergyDepositionThreshold.get()) {
        Deliver<MRPCSD>([&](auto&& r) {
            r.IonizingEnergyDepositionThreshold(fIonizingEnergyDepositionThreshold->GetNewDoubleValue(value));
        });
    }
}

} // namespace MACE::PhaseI::SimMACEPhaseI::inline SD
