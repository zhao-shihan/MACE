#include "MACE/Data/SimDecayVertex.h++"
#include "MACE/SimMACE/Action/TrackingAction.h++"
#include "MACE/Simulation/Physics/Particle/Antimuonium.h++"
#include "MACE/Simulation/Physics/Particle/Muonium.h++"

#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4MuonMinus.hh"
#include "G4MuonPlus.hh"
#include "G4ProcessType.hh"
#include "G4SteppingManager.hh"
#include "G4Track.hh"
#include "G4TrackingManager.hh"
#include "G4VProcess.hh"

#include <cassert>
#include <vector>

namespace MACE::SimMACE::inline Action {

auto TrackingAction::PostUserTrackingAction(const G4Track* track) -> void {
    if (auto& eventManager{*G4EventManager::GetEventManager()};
        eventManager.GetTrackingManager()
            ->GetSteppingManager()
            ->GetfCurrentProcess()
            ->GetProcessType() == fDecay) {
        assert(track->GetStep()->GetSecondary()->size() >= 2);
        std::vector<int> secondaryPDGID;
        secondaryPDGID.reserve(track->GetStep()->GetSecondary()->size());
        for (auto&& track : *track->GetStep()->GetSecondary()) {
            secondaryPDGID.emplace_back(track->GetParticleDefinition()->GetPDGEncoding());
        }
        auto& vertex{fDecayVertexData.emplace_back(std::make_unique_for_overwrite<MACE::Data::Tuple<Data::SimDecayVertex>>())};
        Get<"EvtID">(*vertex) = eventManager.GetConstCurrentEvent()->GetEventID();
        Get<"TrkID">(*vertex) = track->GetTrackID();
        Get<"PDGID">(*vertex) = track->GetParticleDefinition()->GetPDGEncoding();
        Get<"SecPDGID">(*vertex) = std::move(secondaryPDGID);
        Get<"t">(*vertex) = track->GetGlobalTime();
        Get<"x">(*vertex) = track->GetPosition();
        Get<"Ek">(*vertex) = track->GetKineticEnergy();
        Get<"p">(*vertex) = track->GetMomentum();
    }
}

} // namespace MACE::SimMACE::inline Action
