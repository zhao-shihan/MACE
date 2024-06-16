#include "Mustard/Env/MPIEnv.h++"
#include "Mustard/Extension/CLHEPX/Random/Xoshiro.h++"
#include "Mustard/Extension/Geant4X/DecayChannel/MuonInternalPairProductionDecayChannel.h++"
#include "Mustard/Extension/MPIX/Execution/Executor.h++"
#include "Mustard/Extension/MPIX/ParallelizePath.h++"
#include "Mustard/Utility/MPIReseedRandomEngine.h++"

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

auto main(int argc, char* argv[]) -> int {
    Mustard::Env::MPIEnv env{argc, argv, {}};

    Mustard::CLHEPX::Random::Xoshiro256Plus rng;
    CLHEP::HepRandom::setTheEngine(&rng);
    Mustard::MPIReseedRandomEngine();

    G4ParticleTable::GetParticleTable()->SetReadiness();
    G4AntiNeutrinoE::Definition();
    G4AntiNeutrinoMu::Definition();
    G4Electron::Definition();
    G4MuonMinus::Definition();
    G4MuonPlus::Definition();
    G4NeutrinoE::Definition();
    G4NeutrinoMu::Definition();
    G4Positron::Definition();

    Mustard::Geant4X::MuonInternalPairProductionDecayChannel ippDecay{"mu+", 1};
    ippDecay.MetropolisDelta(std::stod(argv[2]));
    ippDecay.MetropolisDiscard(std::stod(argv[3]));
    // if (argc >= 5) { ippDecay.ApplyMACEPxyCut(std::stoll(argv[4])); }

    TFile file{Mustard::MPIX::ParallelizePath("mu2eeevv.root").generic_string().c_str(), "RECREATE", "", ROOT::RCompressionSetting::EDefaults::kUseGeneralPurpose};
    TNtuple t{"eeevv", "eeevv", "e1:e2:e3:e4:e5"};

    Mustard::MPIX::Executor<unsigned long long> executor;
    executor.Execute(std::stoull(argv[1]),
                     [&](auto) {
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
