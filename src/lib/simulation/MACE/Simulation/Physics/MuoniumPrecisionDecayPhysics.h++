#pragma once

#include "MACE/Simulation/Physics/MuonPrecisionDecayPhysics.h++"

namespace MACE::inline Simulation::inline Physics {

class MuoniumPrecisionDecayPhysics final : public MuonPrecisionDecayPhysics {
public:
    MuoniumPrecisionDecayPhysics(G4int verbose);

    auto ConstructProcess() -> void override;

private:
    auto UpdateBR() -> void override;
};

} // namespace MACE::inline Simulation::inline Physics
