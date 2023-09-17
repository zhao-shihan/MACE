#pragma once

#include "MACE/Env/Memory/PassiveSingleton.h++"

#include "G4Types.hh"
#include "G4UserTrackingAction.hh"

#include "gsl/gsl"

class G4ParticleDefinition;

namespace MACE::inline Simulation::SimTarget {

class MuoniumTrack;

inline namespace Action {

class TrackingAction final : public Env::Memory::PassiveSingleton<TrackingAction>,
                             public G4UserTrackingAction {
public:
    TrackingAction();

    void EventID(G4int id) { fEventID = id; }

    void PreUserTrackingAction(const G4Track* track) override;
    void PostUserTrackingAction(const G4Track* track) override;

private:
    const gsl::not_null<const G4ParticleDefinition*> fMuonium;
    const gsl::not_null<const G4ParticleDefinition*> fAntimuonium;
    MuoniumTrack* fMuoniumTrack;
    G4int fEventID;
};

} // namespace Action

} // namespace MACE::inline Simulation::SimTarget
