#pragma once

#include "G4VDecayChannel.hh"

namespace MACE::inline Simulation::inline Physics::inline DecayChannel {

class MuonInternalPairProductionDecayChannel final : public G4VDecayChannel {
public:
    MuonInternalPairProductionDecayChannel(const G4String& parentName, G4double br, G4int verbose = 1);

    auto DecayIt(G4double) -> G4DecayProducts* override;
};

} // namespace MACE::inline Simulation::inline Physics::inline DecayChannel
