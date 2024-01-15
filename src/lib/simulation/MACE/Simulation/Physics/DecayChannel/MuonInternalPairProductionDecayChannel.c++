#include "MACE/Simulation/Physics/DecayChannel/MuonInternalPairProductionDecayChannel.h++"

#include "G4AntiNeutrinoE.hh"
#include "G4AntiNeutrinoMu.hh"
#include "G4DecayProducts.hh"
#include "G4DynamicParticle.hh"
#include "G4Electron.hh"
#include "G4NeutrinoE.hh"
#include "G4NeutrinoMu.hh"
#include "G4Positron.hh"

namespace MACE::inline Simulation::inline Physics::inline DecayChannel {

MuonInternalPairProductionDecayChannel::MuonInternalPairProductionDecayChannel(const G4String& parentName, G4double br, G4int verbose) :
    G4VDecayChannel{"MuonIPPDecay", verbose} {
    SetParent(parentName);
    SetBR(br);
    SetNumberOfDaughters(5);
    if (parentName == "mu+") {
        SetDaughter(0, G4Positron::Definition());
        SetDaughter(1, G4NeutrinoE::Definition());
        SetDaughter(2, G4AntiNeutrinoMu::Definition());
        SetDaughter(3, G4Electron::Definition());
        SetDaughter(4, G4Positron::Definition());
    } else if (parentName == "mu-") {
        SetDaughter(0, G4Electron::Definition());
        SetDaughter(1, G4AntiNeutrinoE::Definition());
        SetDaughter(2, G4NeutrinoMu::Definition());
        SetDaughter(3, G4Positron::Definition());
        SetDaughter(3, G4Electron::Definition());
    } else {
#ifdef G4VERBOSE
        if (GetVerboseLevel() > 0) {
            G4cout << "MuonInternalPairProductionDecayChannel::(Constructor) says\n"
                      "\tParent particle is not mu+ or mu- but "
                   << parentName << G4endl;
        }
#endif
    }
}

auto MuonInternalPairProductionDecayChannel::DecayIt(G4double) -> G4DecayProducts* {
    using namespace PhysicalConstant;
    // using namespace MathConstant;

    // Tree level mu -> eeevv (2 diagrams)

#ifdef G4VERBOSE
    if (GetVerboseLevel() > 1) {
        G4cout << "MuonInternalPairProductionDecayChannel::DecayIt ";
    }
#endif

    CheckAndFillParent();
    CheckAndFillDaughters();

    auto products = new G4DecayProducts(G4DynamicParticle(G4MT_parent, G4ThreeVector(), 0.0));

    // products->PushProducts(new G4DynamicParticle(G4MT_daughters[0], direction0 * daughtermomentum[0]));

    // products->PushProducts(new G4DynamicParticle(G4MT_daughters[1], direction1 * daughtermomentum[1]));

    // products->PushProducts(new G4DynamicParticle(G4MT_daughters[2], direction2 * daughtermomentum[2]));

    // products->PushProducts(new G4DynamicParticle(G4MT_daughters[3], atomicShellMomentum));

    // output message
#ifdef G4VERBOSE
    if (GetVerboseLevel() > 1) {
        G4cout << "MuonInternalPairProductionDecayChannel::DecayIt\n"
                  "\tCreate decay products in rest frame."
               << G4endl;
        products->DumpInfo();
    }
#endif
    return products;
}

} // namespace MACE::inline Simulation::inline Physics::inline DecayChannel
