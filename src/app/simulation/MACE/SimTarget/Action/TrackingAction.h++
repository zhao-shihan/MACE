#pragma once

#include "MACE/Env/Memory/PassiveSingleton.h++"

#include "G4Types.hh"
#include "G4UserTrackingAction.hh"

#include "gsl/gsl"

class G4ParticleDefinition;

namespace MACE::SimTarget {

class MuoniumTrack;

inline namespace Action {

class TrackingAction final : public Env::Memory::PassiveSingleton<TrackingAction>,
                             public G4UserTrackingAction {
public:
    TrackingAction();

    auto EventID(G4int id) -> void { fEventID = id; }

    auto PreUserTrackingAction(const G4Track* track) -> void override;
    auto PostUserTrackingAction(const G4Track* track) -> void override;

private:
    const gsl::not_null<const G4ParticleDefinition*> fMuonium;
    const gsl::not_null<const G4ParticleDefinition*> fAntimuonium;
    MuoniumTrack* fMuoniumTrack;
    G4int fEventID;
};

} // namespace Action

} // namespace MACE::SimTarget
