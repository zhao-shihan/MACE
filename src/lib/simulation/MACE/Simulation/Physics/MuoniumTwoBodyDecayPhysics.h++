#pragma once

#include "MACE/Simulation/Physics/MuonPrecisionDecayPhysics.h++"
#include "MACE/Simulation/Physics/MuoniumTwoBodyDecayPhysicsMessenger.h++"

#include "gsl/gsl"

class G4DecayTable;
class G4String;

namespace MACE::inline Simulation::inline Physics {

class MuoniumTwoBodyDecayPhysics : public MuonPrecisionDecayPhysics {

public:
    MuoniumTwoBodyDecayPhysics(G4int verbose);

    auto AnnihilationBR(double br) -> void { fAnnihilationBR = Math::Clamp<"[]">(br, 0., 1.); }
    auto TwoBodyDecayBR(double br) -> void { fTwoBodyDecayBR = Math::Clamp<"[]">(br, 0., 1.); }

    virtual auto ConstructParticle() -> void override;
    virtual auto ConstructProcess() -> void override;
    virtual auto UpdateDecayBR() -> void override;

protected:
    virtual auto InsertDecayChannel(const G4String& parentName, gsl::not_null<G4DecayTable*> decay) -> void override;
    virtual auto AssignRareDecayBR(gsl::not_null<G4DecayTable*> decay) -> void override;

protected:
    double fAnnihilationBR;
    double fTwoBodyDecayBR;

private:
    MuoniumTwoBodyDecayPhysicsMessenger::Register<MuoniumTwoBodyDecayPhysics> fMessengerRegister;
};

} // namespace MACE::inline Simulation::inline Physics
