#include "MACE/Env/BasicEnv.h++"
#include "MACE/Simulation/Physics/DecayChannel/MuonInternalPairProductionDecayChannel.h++"

#include "TFile.h"
#include "TNtuple.h"

#include "G4AntiNeutrinoE.hh"
#include "G4AntiNeutrinoMu.hh"
#include "G4DecayProducts.hh"
#include "G4DynamicParticle.hh"
#include "G4Electron.hh"
#include "G4MuonMinus.hh"
#include "G4MuonPlus.hh"
#include "G4NeutrinoE.hh"
#include "G4NeutrinoMu.hh"
#include "G4ParticleTable.hh"
#include "G4Positron.hh"

using namespace MACE;

auto main(int argc, char* argv[]) -> int {
    Env::BasicEnv env{argc, argv, {}};

    G4ParticleTable::GetParticleTable()->SetReadiness();
    G4AntiNeutrinoE::Definition();
    G4AntiNeutrinoMu::Definition();
    G4Electron::Definition();
    G4MuonMinus::Definition();
    G4MuonPlus::Definition();
    G4NeutrinoE::Definition();
    G4NeutrinoMu::Definition();
    G4Positron::Definition();

    MuonInternalPairProductionDecayChannel ippDecay{"mu+", 1};

    TFile file{"mu2eeevv.root", "RECREATE"};
    TNtuple t{"eeevv", "eeevv", "e1:e2:e3:e4:e5"};

    const auto n{std::stoull(argv[1])};
    for (auto i{0ull}; i < n; ++i) {
        const auto product{ippDecay.DecayIt(0)};
        const auto v2{product->PopProducts()};
        const auto v1{product->PopProducts()};
        const auto e3{product->PopProducts()};
        const auto e2{product->PopProducts()};
        const auto e1{product->PopProducts()};
        t.Fill(e1->GetTotalEnergy(),
               e2->GetTotalEnergy(),
               e3->GetTotalEnergy(),
               v1->GetTotalEnergy(),
               v2->GetTotalEnergy());
        delete product;
    }

    t.Write();

    return EXIT_SUCCESS;
}
