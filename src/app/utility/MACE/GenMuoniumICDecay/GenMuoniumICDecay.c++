#include "MACE/GenMuoniumICDecay/GenMuoniumICDecay.h++"

#include "Mustard/Env/MPIEnv.h++"
#include "Mustard/Extension/CLHEPX/Random/Xoshiro.h++"
#include "Mustard/Extension/Geant4X/DecayChannel/MuoniumInternalConversionDecayChannel.h++"
#include "Mustard/Extension/Geant4X/Particle/Antimuonium.h++"
#include "Mustard/Extension/Geant4X/Particle/Muonium.h++"
#include "Mustard/Extension/MPIX/Execution/Executor.h++"
#include "Mustard/Extension/MPIX/ParallelizePath.h++"
#include "Mustard/Utility/LiteralUnit.h++"
#include "Mustard/Utility/PhysicalConstant.h++"
#include "Mustard/Utility/UseXoshiro.h++"

#include "TFile.h"
#include "TNtuple.h"

#include "G4AntiNeutrinoE.hh"
#include "G4AntiNeutrinoMu.hh"
#include "G4DecayProducts.hh"
#include "G4DynamicParticle.hh"
#include "G4Electron.hh"
#include "G4LorentzVector.hh"
#include "G4MuonMinus.hh"
#include "G4MuonPlus.hh"
#include "G4NeutrinoE.hh"
#include "G4NeutrinoMu.hh"
#include "G4ParticleTable.hh"
#include "G4Positron.hh"

#include <cmath>

namespace MACE::GenMuoniumICDecay {

using namespace Mustard::LiteralUnit::Energy;
using namespace Mustard::PhysicalConstant;

GenMuoniumICDecay::GenMuoniumICDecay() :
    Subprogram{"GenMuoniumICDecay", "Generate muonium internal conversion decay (M->eeevve) events for physical investigation or test purpose."} {}

auto GenMuoniumICDecay::Main(int argc, char* argv[]) const -> int {
    Mustard::Env::MPIEnv env{argc, argv, {}};

    Mustard::UseXoshiro<256> random;

    G4ParticleTable::GetParticleTable()->SetReadiness();
    Mustard::Geant4X::Antimuonium::Definition();
    G4AntiNeutrinoE::Definition();
    G4AntiNeutrinoMu::Definition();
    G4Electron::Definition();
    G4MuonMinus::Definition();
    G4MuonPlus::Definition();
    G4NeutrinoE::Definition();
    G4NeutrinoMu::Definition();
    G4Positron::Definition();
    Mustard::Geant4X::Muonium::Definition();

    Mustard::Geant4X::MuoniumInternalConversionDecayChannel ippDecay{"anti_muonium", 1};
    ippDecay.MetropolisDelta(std::stod(argv[2]));
    ippDecay.MetropolisDiscard(std::stod(argv[3]));
    if (argc >= 5) {
        ippDecay.Bias(
            [](auto&& event) {
                const auto& [p, p1, p2, k1, k2]{event};
                return p.e() < electron_mass_c2 + 10_keV;
            });
    }

    TFile file{Mustard::MPIX::ParallelizePath("M2eeevve.root").generic_string().c_str(), "RECREATE", "", ROOT::RCompressionSetting::EDefaults::kUseGeneralPurpose};
    TNtuple t{"eeevve", "eeevve", "Ek1:pT1:eta1:Ek2:pT2:eta2:Ek3:pT3:eta3:Ek6"};

    const auto Eta{
        [](const G4DynamicParticle* product) {
            const auto p{product->GetMomentum().mag()};
            const auto pz{product->GetMomentum().z()};
            return std::log((p + pz) / (p - pz)) / 2;
        }};

    Mustard::MPIX::Executor<unsigned long long> executor;
    executor.Execute(std::stoull(argv[1]),
                     [&](auto) {
                         const auto product{ippDecay.DecayIt(0)};
                         const auto e4{product->PopProducts()};
                         const auto v2{product->PopProducts()};
                         const auto v1{product->PopProducts()};
                         const auto e3{product->PopProducts()};
                         const auto e2{product->PopProducts()};
                         const auto e1{product->PopProducts()};
                         t.Fill(e1->GetKineticEnergy(),
                                e1->GetMomentum().perp(),
                                Eta(e1),
                                e2->GetKineticEnergy(),
                                e2->GetMomentum().perp(),
                                Eta(e2),
                                e3->GetKineticEnergy(),
                                e3->GetMomentum().perp(),
                                Eta(e3),
                                e4->GetKineticEnergy());
                         delete e4;
                         delete v2;
                         delete v1;
                         delete e3;
                         delete e2;
                         delete e1;
                         delete product;
                     });
    executor.PrintExecutionSummary();

    t.Write();

    return EXIT_SUCCESS;
}

} // namespace MACE::GenMuoniumICDecay
