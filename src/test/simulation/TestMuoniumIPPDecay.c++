#include "MACE/Env/BasicEnv.h++"
#include "MACE/Simulation/Physics/DecayChannel/MuoniumInternalPairProductionDecayChannel.h++"
#include "MACE/Simulation/Physics/Particle/Antimuonium.h++"
#include "MACE/Simulation/Physics/Particle/Muonium.h++"

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

#include "fmt/format.h"

using namespace MACE;

auto main(int argc, char* argv[]) -> int {
    Env::BasicEnv env{argc, argv, {}};

    G4ParticleTable::GetParticleTable()->SetReadiness();
    Antimuonium::Definition();
    G4AntiNeutrinoE::Definition();
    G4AntiNeutrinoMu::Definition();
    G4Electron::Definition();
    G4MuonMinus::Definition();
    G4MuonPlus::Definition();
    G4NeutrinoE::Definition();
    G4NeutrinoMu::Definition();
    G4Positron::Definition();
    Muonium::Definition();

    MuoniumInternalPairProductionDecayChannel ippDecay{"anti_muonium", 1};

    TFile file{"M2eeevve.root", "RECREATE"};
    TNtuple t{"eeevve", "eeevve", "e1:e2:e3:e4:e5:e6"};

    const auto n{std::stoull(argv[1])};
    for (auto i{0ull}; i < n; ++i) {
        const auto product{ippDecay.DecayIt(0)};
        const auto e4{product->PopProducts()};
        const auto v2{product->PopProducts()};
        const auto v1{product->PopProducts()};
        const auto e3{product->PopProducts()};
        const auto e2{product->PopProducts()};
        const auto e1{product->PopProducts()};
        t.Fill(e1->GetTotalEnergy(),
               e2->GetTotalEnergy(),
               e3->GetTotalEnergy(),
               v1->GetTotalEnergy(),
               v2->GetTotalEnergy(),
               e4->GetKineticEnergy());
        delete product;
    }

    t.Write();

    return EXIT_SUCCESS;
}
