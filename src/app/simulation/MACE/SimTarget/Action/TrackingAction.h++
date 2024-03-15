#pragma once

#include "MACE/SimTarget/Analysis.h++"
#include "MACE/Env/Memory/PassiveSingleton.h++"

#include "G4Types.hh"
#include "G4UserTrackingAction.hh"

#include "gsl/gsl"

class G4ParticleDefinition;

namespace MACE::SimTarget {

inline namespace Action {

class TrackingAction final : public Env::Memory::PassiveSingleton<TrackingAction>,
                             public G4UserTrackingAction {
public:
    TrackingAction();

    auto PreUserTrackingAction(const G4Track* track) -> void override;
    auto PostUserTrackingAction(const G4Track* track) -> void override;

private:
    Data::Tuple<MuoniumTrack>* fMuoniumTrack;
};

} // namespace Action

} // namespace MACE::SimTarget
