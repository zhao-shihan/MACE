#pragma once

#include "G4VPhysicsConstructor.hh"

namespace MACE::inline Extension::Geant4X::Physics {

class MuoniumPhysics final : public G4VPhysicsConstructor {
public:
    MuoniumPhysics(G4int verbose);
    ~MuoniumPhysics() = default;
    MuoniumPhysics(const MuoniumPhysics&) = delete;
    MuoniumPhysics& operator=(const MuoniumPhysics&) = delete;

    void ConstructParticle() override;
    void ConstructProcess() override;
};

} // namespace MACE::inline Extension::Geant4X::Physics
