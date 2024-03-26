#include "MACE/Simulation/SD/CDCSD.h++"
#include "MACE/Simulation/SD/CDCSDMessenger.h++"

#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIdirectory.hh"

namespace MACE::inline Simulation::inline SD {

CDCSDMessenger::CDCSDMessenger() :
    SingletonMessenger{},
    fDirectory{},
    fIonizingEnergyDepositionThreshold{},
    fMinNHitForQualifiedTrack{} {

    fDirectory = std::make_unique<G4UIdirectory>("/MACE/SD/CDC/");
    fDirectory->SetGuidance("CDC sensitive detector.");

    fIonizingEnergyDepositionThreshold = std::make_unique<G4UIcmdWithADoubleAndUnit>("/MACE/SD/CDC/IonizingEnergyDepositionThreshold", this);
    fIonizingEnergyDepositionThreshold->SetGuidance("Ionizing energy deposition threshold for a response.");
    fIonizingEnergyDepositionThreshold->SetParameterName("E", false);
    fIonizingEnergyDepositionThreshold->SetUnitCategory("Energy");
    fIonizingEnergyDepositionThreshold->SetRange("E >= 0");
    fIonizingEnergyDepositionThreshold->AvailableForStates(G4State_Idle);

    fMinNHitForQualifiedTrack = std::make_unique<G4UIcmdWithAnInteger>("/MACE/SD/CDC/MinNHitForQualifiedTrack", this);
    fMinNHitForQualifiedTrack->SetGuidance("Minimum number of cells fired in a track.");
    fMinNHitForQualifiedTrack->SetParameterName("N", false);
    fMinNHitForQualifiedTrack->SetRange("N >= 1");
    fMinNHitForQualifiedTrack->AvailableForStates(G4State_Idle);
}

CDCSDMessenger::~CDCSDMessenger() = default;

auto CDCSDMessenger::SetNewValue(G4UIcommand* command, G4String value) -> void {
    if (command == fIonizingEnergyDepositionThreshold.get()) {
        Deliver<CDCSD>([&](auto&& r) {
            r.IonizingEnergyDepositionThreshold(fIonizingEnergyDepositionThreshold->GetNewDoubleValue(value));
        });
    } else if (command == fMinNHitForQualifiedTrack.get()) {
        Deliver<CDCSD>([&](auto&& r) {
            r.MinNHitForQualifiedTrack(fMinNHitForQualifiedTrack->GetNewIntValue(value));
        });
    }
}

} // namespace MACE::inline Simulation::inline SD
