#pragma once

#include "MACE/Env/Memory/FreeSingleton.hxx"

#include "G4Types.hh"
#include "G4UserTrackingAction.hh"

#include "gsl/gsl"

class G4ParticleDefinition;

namespace MACE::SimTarget {

class MuoniumTrack;

namespace Action {


class TrackingAction final : public Env::Memory::FreeSingleton<TrackingAction>,
                             public G4UserTrackingAction {
public:
    TrackingAction();

    void EventID(G4int id) { fEventID = id; }

    void PreUserTrackingAction(const G4Track* track) override;
    void PostUserTrackingAction(const G4Track* track) override;

private:
    const gsl::not_null<const G4ParticleDefinition*> fMuonium;
    const gsl::not_null<const G4ParticleDefinition*> fAntiMuonium;
    MuoniumTrack* fMuoniumTrack;
    G4int fEventID;
};

} // namespace Action

} // namespace MACE::SimTarget
