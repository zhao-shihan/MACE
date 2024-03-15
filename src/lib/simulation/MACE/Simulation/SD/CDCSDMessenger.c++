#include "MACE/Simulation/SD/CDCSD.h++"
#include "MACE/Simulation/SD/CDCSDMessenger.h++"

#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIdirectory.hh"

namespace MACE::inline Simulation::inline SD {

CDCSDMessenger::CDCSDMessenger() :
    SingletonMessenger{},
    fDirectory{},
    fMinIonizingEnergyDepositionForHit{},
    fNMinFiredCellForQualifiedTrack{} {

    fDirectory = std::make_unique<G4UIdirectory>("/MACE/SD/CDC/");
    fDirectory->SetGuidance("CDC sensitive detector.");

    fMinIonizingEnergyDepositionForHit = std::make_unique<G4UIcmdWithADoubleAndUnit>("/MACE/SD/CDC/MinIonizingEnergyDepositionForHit", this);
    fMinIonizingEnergyDepositionForHit->SetGuidance("Minimum ionizing energy deposition in a hit.");
    fMinIonizingEnergyDepositionForHit->SetParameterName("E", false);
    fMinIonizingEnergyDepositionForHit->SetUnitCategory("Energy");
    fMinIonizingEnergyDepositionForHit->SetRange("E >= 0");
    fMinIonizingEnergyDepositionForHit->AvailableForStates(G4State_Idle);

    fNMinFiredCellForQualifiedTrack = std::make_unique<G4UIcmdWithAnInteger>("/MACE/SD/CDC/NMinFiredCellForQualifiedTrack", this);
    fNMinFiredCellForQualifiedTrack->SetGuidance("Minimum number of cells fired in a track.");
    fNMinFiredCellForQualifiedTrack->SetParameterName("N", false);
    fNMinFiredCellForQualifiedTrack->SetRange("N >= 1");
    fNMinFiredCellForQualifiedTrack->AvailableForStates(G4State_Idle);
}

CDCSDMessenger::~CDCSDMessenger() = default;

auto CDCSDMessenger::SetNewValue(G4UIcommand* command, G4String value) -> void {
    if (command == fMinIonizingEnergyDepositionForHit.get()) {
        Deliver<CDCSD>([&](auto&& r) {
            r.MinIonizingEnergyDepositionForHit(fMinIonizingEnergyDepositionForHit->GetNewDoubleValue(value));
        });
    } else if (command == fNMinFiredCellForQualifiedTrack.get()) {
        Deliver<CDCSD>([&](auto&& r) {
            r.NMinFiredCellForQualifiedTrack(fNMinFiredCellForQualifiedTrack->GetNewIntValue(value));
        });
    }
}

} // namespace MACE::inline Simulation::inline SD
