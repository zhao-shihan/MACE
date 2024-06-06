#pragma once

#include "MACE/Simulation/Physics/DecayPhysicsBase.h++"
#include "MACE/Simulation/Physics/MuonPrecisionDecayPhysicsMessenger.h++"

#include "muc/math"

#include "gsl/gsl"

class G4DecayTable;
class G4ParticleDefinition;
class G4String;

namespace MACE::inline Simulation::inline Physics {

class MuonPrecisionDecayPhysics : public DecayPhysicsBase {
public:
    MuonPrecisionDecayPhysics(G4int verbose);

    auto RadiativeDecayBR(double br) -> void { fRadiativeDecayBR = muc::clamp<"[]">(br, 0., 1.); }
    auto IPPDecayBR(double br) -> void { fIPPDecayBR = muc::clamp<"[]">(br, 0., 1.); }
    virtual auto UpdateDecayBR() -> void;

    virtual auto ConstructParticle() -> void override;
    virtual auto ConstructProcess() -> void override;

protected:
    virtual auto InsertDecayChannel(const G4String& parentName, gsl::not_null<G4DecayTable*> decay) -> void;
    virtual auto AssignRareDecayBR(gsl::not_null<G4DecayTable*> decay) -> void;

protected:
    double fRadiativeDecayBR;
    double fIPPDecayBR;

private:
    MuonPrecisionDecayPhysicsMessenger::Register<MuonPrecisionDecayPhysics> fMessengerRegister;
};

} // namespace MACE::inline Simulation::inline Physics
