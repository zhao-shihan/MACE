#pragma once

#include "MACE/Math/Clamp.h++"
#include "MACE/Simulation/Physics/DecayPhysicsBase.h++"

#include "gsl/gsl"

class G4DecayTable;
class G4String;

namespace MACE::inline Simulation::inline Physics {

class MuoniumPrecisionDecayPhysics : public DecayPhysicsBase {
public:
    MuoniumPrecisionDecayPhysics(G4int verbose);

    auto RadiativeDecayBR(double br) -> void { fRadiativeDecayBR = Math::Clamp<"[]">(br, 0., 1.); }
    auto IPPDecayBR(double br) -> void { fIPPDecayBR = Math::Clamp<"[]">(br, 0., 1.); }

    virtual auto ConstructParticle() -> void override;
    virtual auto ConstructProcess() -> void override;

protected:
    virtual auto UpdateDecayBR() -> void override;
    virtual auto InsertDecayChannel(const G4String& parentName, gsl::not_null<G4DecayTable*> decay) -> void override;
    virtual auto AssignRareDecayBR(gsl::not_null<G4DecayTable*> decay) -> void override;

protected:
    double fRadiativeDecayBR;
    double fIPPDecayBR;
};

} // namespace MACE::inline Simulation::inline Physics
