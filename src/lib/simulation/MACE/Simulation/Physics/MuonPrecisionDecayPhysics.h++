#pragma once

#include "MACE/Simulation/Physics/MuonPrecisionDecayPhysicsMessenger.h++"
#include "MACE/Utility/NonMoveableBase.h++"

#include "G4VPhysicsConstructor.hh"

class G4DecayTable;

namespace MACE::inline Simulation::inline Physics {

class MuonPrecisionDecayPhysics : public NonMoveableBase,
                                  public G4VPhysicsConstructor {
public:
    MuonPrecisionDecayPhysics(G4int verbose);

    auto IPPDecayBR(double br) -> void;

    virtual auto ConstructParticle() -> void override;
    virtual auto ConstructProcess() -> void override;

protected:
    static auto CheckAndSetMainChannelBR(const G4DecayTable* decay) -> void;

protected:
    bool fProcessConstructed;

    double fIPPDecayBR;

    MuonPrecisionDecayPhysicsMessenger::Register<MuonPrecisionDecayPhysics> fMessengerRegister;
};

} // namespace MACE::inline Simulation::inline Physics
