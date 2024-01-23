#pragma once

#include "MACE/Utility/NonMoveableBase.h++"

#include "G4VPhysicsConstructor.hh"

namespace MACE::inline Simulation::inline Physics {

class MuonPrecisionDecayPhysics final : public NonMoveableBase,
                                        public G4VPhysicsConstructor {
public:
    MuonPrecisionDecayPhysics(G4int verbose);

    auto ConstructParticle() -> void override;
    auto ConstructProcess() -> void override;

private:
    static constexpr auto fgMuonIPPDecayBR{3.4e-5};
};

} // namespace MACE::inline Simulation::inline Physics
