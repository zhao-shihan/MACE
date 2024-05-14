#pragma once

#include "MACE/Math/Clamp.h++"
#include "MACE/Simulation/Physics/DecayPhysicsBase.h++"
#include "MACE/Simulation/Physics/MuoniumTwoBodyDecayPhysicsMessenger.h++"

#include "gsl/gsl"

class G4DecayTable;
class G4String;

namespace MACE::inline Simulation::inline Physics {

class MuoniumTwoBodyDecayPhysics : public DecayPhysicsBase {

public:
    MuoniumTwoBodyDecayPhysics(G4int verbose);

    auto RadiativeDecayBR(double br) -> void { fRadiativeDecayBR = Math::Clamp<"[]">(br, 0., 1.); }
    auto IPPDecayBR(double br) -> void { fIPPDecayBR = Math::Clamp<"[]">(br, 0., 1.); }
    auto AnnihilationBR(double br) -> void { fAnnihilationBR = Math::Clamp<"[]">(br, 0., 1.); }
    auto TwoBodyDecayBR(double br) -> void { fTwoBodyDecayBR = Math::Clamp<"[]">(br, 0., 1.); }

    virtual auto ConstructParticle() -> void override;
    virtual auto ConstructProcess() -> void override;
    virtual auto UpdateDecayBR() -> void override;

protected:
    virtual auto InsertDecayChannel(const G4String& parentName, gsl::not_null<G4DecayTable*> decay) -> void override;
    virtual auto AssignRareDecayBR(gsl::not_null<G4DecayTable*> decay) -> void override;

protected:
    double fRadiativeDecayBR;
    double fIPPDecayBR;
    double fAnnihilationBR;
    double fTwoBodyDecayBR;

private:
    MuoniumTwoBodyDecayPhysicsMessenger::Register<MuoniumTwoBodyDecayPhysics> fMessengerRegister;
};

} // namespace MACE::inline Simulation::inline Physics
