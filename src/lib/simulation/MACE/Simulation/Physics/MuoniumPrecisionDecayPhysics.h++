#pragma once

#include "MACE/Simulation/Physics/MuonPrecisionDecayPhysics.h++"

#include "gsl/gsl"

class G4DecayTable;
class G4String;

namespace MACE::inline Simulation::inline Physics {

class MuoniumPrecisionDecayPhysics : public MuonPrecisionDecayPhysics {
public:
    MuoniumPrecisionDecayPhysics(G4int verbose);

    virtual auto ConstructParticle() -> void override;
    virtual auto ConstructProcess() -> void override;

protected:
    virtual auto UpdateBR() -> void override;
    virtual auto InsertDecayChannel(const G4String& parentName, gsl::not_null<G4DecayTable*> decay) -> void override;
    virtual auto AssignRareDecayBR(gsl::not_null<G4DecayTable*> decay) -> void override;
};

} // namespace MACE::inline Simulation::inline Physics
