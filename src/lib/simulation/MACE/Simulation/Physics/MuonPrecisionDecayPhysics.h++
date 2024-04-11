#pragma once

#include "MACE/Math/Clamp.h++"
#include "MACE/Simulation/Physics/MuonPrecisionDecayPhysicsMessenger.h++"
#include "MACE/Utility/NonMoveableBase.h++"

#include "G4VPhysicsConstructor.hh"

#include "gsl/gsl"

class G4DecayTable;
class G4ParticleDefinition;
class G4String;

namespace MACE::inline Simulation::inline Physics {

class MuonPrecisionDecayPhysics : public NonMoveableBase,
                                  public G4VPhysicsConstructor {
public:
    MuonPrecisionDecayPhysics(G4int verbose);

    auto RadiativeDecayBR(double br) -> void { fRadiativeDecayBR = Math::Clamp<"[]">(br, 0., 1.); }
    auto IPPDecayBR(double br) -> void { fIPPDecayBR = Math::Clamp<"[]">(br, 0., 1.); }
    virtual auto UpdateDecayBR() -> void;

    virtual auto ConstructParticle() -> void override;
    virtual auto ConstructProcess() -> void override;

protected:
    auto UpdateDecayBRFor(const G4ParticleDefinition* mu) -> void;
    virtual auto InsertDecayChannel(const G4String& parentName, gsl::not_null<G4DecayTable*> decay) -> void;
    virtual auto AssignRareDecayBR(gsl::not_null<G4DecayTable*> decay) -> void;

protected:
    double fRadiativeDecayBR;
    double fIPPDecayBR;

private:
    MuonPrecisionDecayPhysicsMessenger::Register<MuonPrecisionDecayPhysics> fMessengerRegister;
};

} // namespace MACE::inline Simulation::inline Physics
