#pragma once

#include "MACE/Simulation/Physics/MuonPrecisionDecayPhysicsMessenger.h++"
#include "MACE/Utility/NonMoveableBase.h++"

#include "G4VPhysicsConstructor.hh"

class G4ParticleDefinition;

namespace MACE::inline Simulation::inline Physics {

class MuonPrecisionDecayPhysics : public NonMoveableBase,
                                  public G4VPhysicsConstructor {
public:
    MuonPrecisionDecayPhysics(G4int verbose);

    auto IPPDecayBR(double br) -> void;

    virtual auto ConstructParticle() -> void override { UpdateBR(); }
    virtual auto ConstructProcess() -> void override;

protected:
    virtual auto UpdateBR() -> void;

    auto UpdateBRFor(const G4ParticleDefinition* mu) -> void;

protected:
    double fIPPDecayBR;

    bool fDecayTableConstructed;

    MuonPrecisionDecayPhysicsMessenger::Register<MuonPrecisionDecayPhysics> fMessengerRegister;
};

} // namespace MACE::inline Simulation::inline Physics
