#include "MACE/Detector/Description/CDC.h++"
#include "MACE/Detector/Description/MMSField.h++"
#include "MACE/Detector/Description/TTC.h++"
#include "MACE/GenMuonICDecay/GenMuonICDecay.h++"

#include "Mustard/Env/MPIEnv.h++"
#include "Mustard/Extension/CLHEPX/Random/Xoshiro.h++"
#include "Mustard/Extension/Geant4X/DecayChannel/MuonInternalConversionDecayChannel.h++"
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
#include "G4ThreeVector.hh"

#include "muc/numeric"

#include <cmath>

namespace MACE::GenMuonICDecay {

using namespace Mustard::LiteralUnit::Energy;
using namespace Mustard::PhysicalConstant;

GenMuonICDecay::GenMuonICDecay() :
    Subprogram{"GenMuonICDecay", "Generate muon internal conversion decay (mu->eeevv) events for physical investigation or test purpose."} {}

auto GenMuonICDecay::Main(int argc, char* argv[]) const -> int {
    Mustard::Env::MPIEnv env{argc, argv, {}};

    Mustard::UseXoshiro<256> random;

    G4ParticleTable::GetParticleTable()->SetReadiness();
    G4AntiNeutrinoE::Definition();
    G4AntiNeutrinoMu::Definition();
    G4Electron::Definition();
    G4MuonMinus::Definition();
    G4MuonPlus::Definition();
    G4NeutrinoE::Definition();
    G4NeutrinoMu::Definition();
    G4Positron::Definition();

    Mustard::Geant4X::MuonInternalConversionDecayChannel ippDecay{"mu+", 1};
    ippDecay.MetropolisDelta(std::stod(argv[2]));
    ippDecay.MetropolisDiscard(std::stod(argv[3]));
    if (argc >= 5) {
        // ippDecay.Bias(
        //     [](auto&& event) {
        //         const auto& [p, p1, p2, k1, k2]{event};
        //         return p.e() < electron_mass_c2 + 10_keV;
        //     });
        ippDecay.Bias(
            [](auto&& event) {
                constexpr auto fMACEBiasPxySofteningFactor{0.2_MeV};
                constexpr auto fMACEBiasCosSofteningFactor{0.05};
                constexpr auto fMACEBiasEkLow{5_keV};
                constexpr auto fMACEBiasEkSofteningFactor{1_keV};

                const muc::soft_cmp scPxy{fMACEBiasPxySofteningFactor};
                const muc::soft_cmp scCos{fMACEBiasCosSofteningFactor};
                const muc::soft_cmp scEk{fMACEBiasEkSofteningFactor};

                const auto& cdc{Detector::Description::CDC::Instance()};
                const auto& ttc{Detector::Description::TTC::Instance()};
                const auto mmsB{Detector::Description::MMSField::Instance().FastField()};
                const auto inPxyCut{scPxy((cdc.GasInnerRadius() / 2) * mmsB * c_light)};
                const auto outPxyCut{scPxy((ttc.Radius() / 2) * mmsB * c_light)};
                const auto cosCut{scCos(1 / muc::hypot(2 * cdc.GasOuterRadius() / cdc.GasOuterLength(), 1.))};
                const auto lowEkCut{scEk(fMACEBiasEkLow)};

                // .         e+ e-  e+  v   v
                const auto& [p, p1, p2, k1, k2]{event};
                const auto p1Seen{scPxy(muc::hypot(p1.x(), p1.y())) > outPxyCut and scCos(muc::abs(p1.cosTheta())) < cosCut};
                const auto pMiss{scPxy(muc::hypot(p.x(), p.y())) < inPxyCut or scCos(muc::abs(p.cosTheta())) > cosCut};
                const auto p2Miss{scPxy(muc::hypot(p2.x(), p2.y())) < inPxyCut or scCos(muc::abs(p2.cosTheta())) > cosCut};
                const auto pLow{scEk(p.e() - electron_mass_c2) < lowEkCut};
                const auto p2Low{scEk(p2.e() - electron_mass_c2) < lowEkCut};
                return p1Seen and ((pMiss and p2Low) or (p2Miss and pLow));
            });
    }

    TFile file{Mustard::MPIX::ParallelizePath("mu2eeevv.root").generic_string().c_str(), "RECREATE", "", ROOT::RCompressionSetting::EDefaults::kUseGeneralPurpose};
    TNtuple t{"eeevv", "eeevv", "Ek1:pT1:eta1:Ek2:pT2:eta2:Ek3:pT3:eta3:w"};

    const auto Eta{
        [](const G4DynamicParticle* product) {
            const auto p{product->GetMomentum().mag()};
            const auto pz{product->GetMomentum().z()};
            return std::log((p + pz) / (p - pz)) / 2;
        }};

    ippDecay.Initialize();

    Mustard::MPIX::Executor<unsigned long long> executor;
    executor.Execute(std::stoull(argv[1]),
                     [&](auto) {
                         const auto product{ippDecay.DecayIt(muonium_mass_c2)};
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
                                ippDecay.Weight());
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

} // namespace MACE::GenMuonICDecay
