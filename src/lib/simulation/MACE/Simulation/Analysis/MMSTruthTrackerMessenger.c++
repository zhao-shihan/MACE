#include "MACE/Simulation/Analysis/MMSTruthTracker.h++"
#include "MACE/Simulation/Analysis/MMSTruthTrackerMessenger.h++"

#include "G4UIcmdWithAnInteger.hh"

namespace MACE::inline Simulation::Analysis {

MMSTruthTrackerMessenger::MMSTruthTrackerMessenger() :
    SingletonMessenger{},
    fMinNCDCHitForQualifiedTrack{},
    fMinNTTCHitForQualifiedTrack{} {

    fMinNCDCHitForQualifiedTrack = std::make_unique<G4UIcmdWithAnInteger>("/MACE/Analysis/MinNCDCHitForQualifiedTrack", this);
    fMinNCDCHitForQualifiedTrack->SetGuidance("Minimum number of CDC cell hits in a track.");
    fMinNCDCHitForQualifiedTrack->SetParameterName("N", false);
    fMinNCDCHitForQualifiedTrack->SetRange("N >= 1");
    fMinNCDCHitForQualifiedTrack->AvailableForStates(G4State_Idle);

    fMinNTTCHitForQualifiedTrack = std::make_unique<G4UIcmdWithAnInteger>("/MACE/Analysis/MinNTTCHitForQualifiedTrack", this);
    fMinNTTCHitForQualifiedTrack->SetGuidance("Minimum number of TTC tile hits in a track.");
    fMinNTTCHitForQualifiedTrack->SetParameterName("N", false);
    fMinNTTCHitForQualifiedTrack->SetRange("N >= 1");
    fMinNTTCHitForQualifiedTrack->AvailableForStates(G4State_Idle);
}

MMSTruthTrackerMessenger::~MMSTruthTrackerMessenger() = default;

auto MMSTruthTrackerMessenger::SetNewValue(G4UIcommand* command, G4String value) -> void {
    if (command == fMinNCDCHitForQualifiedTrack.get()) {
        Deliver<MMSTruthTracker>([&](auto&& r) {
            r.MinNCDCHitForQualifiedTrack(fMinNCDCHitForQualifiedTrack->GetNewIntValue(value));
        });
    } else if (command == fMinNTTCHitForQualifiedTrack.get()) {
        Deliver<MMSTruthTracker>([&](auto&& r) {
            r.MinNTTCHitForQualifiedTrack(fMinNTTCHitForQualifiedTrack->GetNewIntValue(value));
        });
    }
}

} // namespace MACE::inline Simulation::Analysis
