#pragma once

#include "MACE/Simulation/Physics/MuonPrecisionDecayPhysics.h++"

namespace MACE::inline Simulation::inline Physics {

class MuoniumPrecisionDecayPhysics final : public MuonPrecisionDecayPhysics {
public:
    MuoniumPrecisionDecayPhysics(G4int verbose);

    auto ConstructParticle() -> void override;
    auto ConstructProcess() -> void override;
};

} // namespace MACE::inline Simulation::inline Physics
