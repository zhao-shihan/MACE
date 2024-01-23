#include "MACE/Simulation/Physics/DecayChannel/MuonInternalPairProductionDecayChannel.h++"

#include "G4AntiNeutrinoE.hh"
#include "G4AntiNeutrinoMu.hh"
#include "G4DecayProducts.hh"
#include "G4DynamicParticle.hh"
#include "G4Electron.hh"
#include "G4NeutrinoE.hh"
#include "G4NeutrinoMu.hh"
#include "G4Positron.hh"

#include "gsl/gsl"

namespace MACE::inline Simulation::inline Physics::inline DecayChannel {

using namespace PhysicalConstant;

MuonInternalPairProductionDecayChannel::MuonInternalPairProductionDecayChannel(const G4String& parentName, G4double br, G4int verbose) : // clang-format off
    G4VDecayChannel{"MuonIPPDecay", verbose}, // clang-format on
    fMetropolisDelta{0.05},
    fMetropolisDiscard{100},
    fMetropolisWarmupCycle{5000000},
    fSameChargedFinalStateEnergyCut{muon_mass_c2},
    fRAMBO{muon_mass_c2, {electron_mass_c2, electron_mass_c2, electron_mass_c2, 0, 0}},
    fRawState{},
    fEvent{},
    fWeightedM2{},
    fMessengerRegister{this} {
    SetParent(parentName);
    SetBR(br);
    SetNumberOfDaughters(5);
    if (parentName == "mu+") {
        SetDaughter(0, G4Positron::Definition());
        SetDaughter(1, G4Electron::Definition());
        SetDaughter(2, G4Positron::Definition());
        SetDaughter(3, G4AntiNeutrinoMu::Definition());
        SetDaughter(4, G4NeutrinoE::Definition());
    } else if (parentName == "mu-") {
        SetDaughter(0, G4Electron::Definition());
        SetDaughter(1, G4Positron::Definition());
        SetDaughter(2, G4Electron::Definition());
        SetDaughter(3, G4NeutrinoMu::Definition());
        SetDaughter(4, G4AntiNeutrinoE::Definition());
    } else {
#ifdef G4VERBOSE
        if (GetVerboseLevel() > 0) {
            G4cout << "MuonInternalPairProductionDecayChannel::(Constructor) says\n"
                      "\tParent particle is not mu+ or mu- but "
                   << parentName << G4endl;
        }
#endif
    }
    Thermalize();
}

auto MuonInternalPairProductionDecayChannel::SameChargedFinalStateEnergyCut(double eUp) -> void {
    if (eUp > electron_mass_c2) {
        fSameChargedFinalStateEnergyCut = eUp;
    } else {
        fSameChargedFinalStateEnergyCut = muon_mass_c2;
    }
    Thermalize();
}

auto MuonInternalPairProductionDecayChannel::DecayIt(G4double) -> G4DecayProducts* {
    // Tree level mu -> eeevv (2 diagrams)

#ifdef G4VERBOSE
    if (GetVerboseLevel() > 1) {
        G4cout << "MuonInternalPairProductionDecayChannel::DecayIt ";
    }
#endif

    CheckAndFillParent();
    CheckAndFillDaughters();

    auto& rng{*G4Random::getTheEngine()};
    for (int i{}; i < fMetropolisDiscard; ++i) {
        UpdateState(rng);
    }
    UpdateState(rng);
    // clang-format off
    auto products{new G4DecayProducts{G4DynamicParticle{G4MT_parent, {}, 0}}}; // clang-format on
    for (int i{}; i < 5; ++i) {
        products->PushProducts(new G4DynamicParticle{G4MT_daughters[i], fEvent.state[i]});
    }

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

auto MuonInternalPairProductionDecayChannel::UpdateState(CLHEP::HepRandomEngine& rng) -> void {
    decltype(fRawState) newRawState;
    decltype(fEvent) newEvent;
    while (true) {
        do {
            rng.flatArray(newRawState.size(), newRawState.data());
            for (gsl::index i{}; i < ssize(newRawState); ++i) {
                newRawState[i] = fMetropolisDelta * (2 * newRawState[i] - 1);
                newRawState[i] += fRawState[i];
            }
            newEvent = fRAMBO(newRawState);
        } while (Cut(newEvent) == false);
        const auto newWeightedM2{WeightedM2(newEvent)};
        if (newWeightedM2 >= fWeightedM2 or
            newWeightedM2 >= fWeightedM2 * rng.flat()) {
            fRawState = newRawState;
            fEvent = newEvent;
            fWeightedM2 = newWeightedM2;
            return;
        }
    }
}

auto MuonInternalPairProductionDecayChannel::Thermalize() -> void {
    auto& rng{*G4Random::getTheEngine()};
    // initialize
    do {
        rng.flatArray(fRawState.size(), fRawState.data());
        fEvent = fRAMBO(fRawState);
    } while (Cut(fEvent) == false);
    fWeightedM2 = WeightedM2(fEvent);
    // warm up cycle
    for (auto i{0}; i < fMetropolisWarmupCycle; ++i) {
        UpdateState(rng);
    }
}

auto MuonInternalPairProductionDecayChannel::Cut(const Math::RAMBO<5>::Event& event) const -> bool {
    const auto& [p, p1, p2, k1, k2]{event.state};
    return p.e() < fSameChargedFinalStateEnergyCut or p2.e() < fSameChargedFinalStateEnergyCut;
}

auto MuonInternalPairProductionDecayChannel::WeightedM2(const Math::RAMBO<5>::Event& event) -> double {
    const auto& [weight, state]{event};
    const auto& [p, p1, p2, k1, k2]{state};

    constexpr auto u2 = muon_mass_c2 * muon_mass_c2;
    constexpr auto m2 = electron_mass_c2 * electron_mass_c2;
    constexpr auto m4 = m2 * m2;

    const auto qp = muon_mass_c2 * p.e();
    const auto qp1 = muon_mass_c2 * p1.e();
    const auto qp2 = muon_mass_c2 * p2.e();
    const auto pp1 = p * p1;
    const auto pp2 = p * p2;
    const auto p1p2 = p1 * p2;
    const auto qk1 = muon_mass_c2 * k1.e();
    const auto qk2 = muon_mass_c2 * k2.e();
    const auto p2k1 = p2 * k1;
    const auto p1k2 = p1 * k2;
    const auto pk1 = p * k1;
    const auto pk2 = p * k2;
    const auto p1k1 = p1 * k1;
    const auto k1k2 = k1 * k2;
    const auto p2k2 = p2 * k2;

    const auto qps = qp * qp;
    const auto qp12 = qp1 * qp1;
    const auto qp22 = qp2 * qp2;
    const auto pp12 = pp1 * pp1;
    const auto pp22 = pp2 * pp2;
    const auto p1p22 = p1p2 * p1p2;

    const auto C1 = 1 / (2 * (m2 + pp1 + pp2 + p1p2));
    const auto C2 = 1 / (2 * (m2 - qp1 - qp2 + p1p2));
    const auto C3 = 1 / (2 * (m2 - qp - qp1 + pp1));
    const auto D1 = 1 / (2 * (m2 + p1p2));
    const auto D2 = 1 / (2 * (m2 + pp1));

    return weight *
           (-20 * C1 * C1 * (2 * D1 * D2 * (m2 * (p2k1 + pk1) * (m2 + p1p2 + // clang-format off
            pp1) - (2 * m2 * (p1k1 + p2k1 + pk1) + (p2k1 + pk1) * (p1p2 +
            pp1)) * pp2 + p1k1 * pp2 * pp2) + D1 * D1 * (m4 * p1k1 + m2 * m2 *
            (p2k1 + 2 * pk1) - p1k1 * p1p2 * pp1 - p1p2 * pk1 * pp1 + p2k1 *
            pp12 - p1p2 * p2k1 * pp2 - p1p2 * pk1 * pp2 - p1k1 * pp1 * pp2 -
            p2k1 * pp1 * pp2 - 2 * pk1 * pp1 * pp2 + m2 * (p1k1 * p1p2 + p1p2 *
            p2k1 + 2 * p1p2 * pk1 - 2 * p1k1 * pp1 - p2k1 * pp1 - pk1 * pp1 -
            (p1k1 + 2 * p2k1 + pk1) * pp2) + p1k1 * pp22) + D2 * D2 * (m4 *
            p1k1 + p1p22 * pk1 + m2 * m2 * (2 * p2k1 + pk1) - (p1p2 * pk1 +
            (p2k1 + pk1) * pp1) * pp2 - m2 * (p1p2 * (p2k1 + pk1) - (2 * p2k1 +
            pk1) * pp1 + (p2k1 + 2 * pk1) * pp2 + p1k1 * (2 * p1p2 - pp1 +
            pp2)) - p1p2 * (p1k1 * (pp1 + pp2) + p2k1 * (pp1 + 2 * pp2)) +
            p1k1 * pp22)) * qk2 + C1 * (C2 * D1 * (20 * D1 * (m2 * m2 * (-2 *
            pk2 * qk1 + 2 * k1k2 * qp) + (p2k2 * pk1 * pp1 - p2k2 * (2 * p1k1 +
            pk1) * pp2 + p2k1 * pp1 * (2 * p2k2 - qk2) + (p1k1 + 2 * pk1) *
            pp2 * qk2) * qp1 + (-(p1k2 * (2 * p2k1 + pk1) * pp1) + p1k2 * (2 *
            p1k1 + pk1) * pp2 + (p2k1 * pp1 + 2 * pk1 * pp1 - p1k1 * pp2) *
            qk2) * qp2 + p1p2 * (-(p2k2 * pp1 * qk1) - p1k2 * pp2 * qk1 + pp1 *
            qk1 * qk2 + pp2 * qk1 * qk2 + p2k2 * (p1k1 + pk1) * qp + p1k2 *
            (p2k1 + pk1) * qp - p1k1 * qk2 * qp - p2k1 * qk2 * qp - 2 * pk1 *
            qk2 * qp - p2k1 * pk2 * qp1 - pk1 * pk2 * qp1 + k1k2 * pp2 * qp1 -
            p1k1 * pk2 * qp2 - pk1 * pk2 * qp2 + k1k2 * pp1 * qp2) + m2 * (-2 *
            p1p2 * pk2 * qk1 + p1k2 * pp1 * qk1 + p2k2 * pp2 * qk1 + pp1 *
            qk1 * qk2 + pp2 * qk1 * qk2 - p1k1 * p1k2 * qp + 2 * k1k2 * p1p2 *
            qp - p2k1 * p2k2 * qp + p1k2 * pk1 * qp + p2k2 * pk1 * qp - p1k1 *
            qk2 * qp - p2k1 * qk2 * qp - 2 * pk1 * qk2 * qp + p1k1 * pk2 *
            qp1 - pk1 * pk2 * qp1 - k1k2 * pp1 * qp1 + p2k1 * pk2 * qp2 -
            pk1 * pk2 * qp2 - k1k2 * pp2 * qp2)) + D2 * (m2 * m2 * ((-p1k2 +
            p2k2 - 2 * pk2) * qk1 + k1k2 * (2 * qp + qp1 - qp2)) + m2 *
            (p1p2 * p2k2 * qk1 - 2 * p1p2 * pk2 * qk1 + p2k2 * pp1 * qk1 +
            p2k2 * pp2 * qk1 + 2 * pp2 * qk1 * qk2 + 2 * k1k2 * p1p2 * qp -
            p1k1 * p2k2 * qp - p2k1 * p2k2 * qp - 2 * p2k1 * qk2 * qp - 2 *
            pk1 * qk2 * qp + k1k2 * p1p2 * qp1 + p1k1 * p2k2 * qp1 + p2k1 *
            p2k2 * qp1 + 4 * p2k2 * pk1 * qp1 + p1k1 * pk2 * qp1 - p2k1 * pk2 *
            qp1 - 2 * pk1 * pk2 * qp1 - k1k2 * pp1 * qp1 + k1k2 * pp2 * qp1 -
            2 * p1k1 * qk2 * qp1 - 2 * p2k1 * qk2 * qp1 - 4 * pk1 * qk2 * qp1 +
            ((p1k1 + p2k1) * pk2 - k1k2 * (p1p2 + pp1 + pp2) + 2 * (p1k1 +
            p2k1 + 2 * pk1) * qk2) * qp2 - p1k2 * ((p1p2 - pp1 + pp2) * qk1 +
            (p1k1 - p2k1 - 2 * pk1) * qp + (p1k1 + p2k1 + 4 * pk1) * qp2)) +
            2 * ((p2k1 * p2k2 * pp1 + p2k2 * pk1 * pp1 - p1k1 * p2k2 * pp2 +
            pk1 * pp2 * qk2) * qp1 + p1p2 * pp2 * (qk1 * qk2 + k1k2 * qp1) -
            p1p2 * (p2k1 + pk1) * (qk2 * qp + pk2 * qp1) + (p2k1 + pk1) * pp1 *
            qk2 * qp2 - p1k1 * pp2 * qk2 * qp2 + p1k2 * (-(p1p2 * pp2 * qk1) +
            p1p2 * (p2k1 + pk1) * qp - (p2k1 + pk1) * pp1 * qp2 + p1k1 * pp2 *
            qp2)))) + C3 * D2 * (20 * D2 * (-(p1k2 * pp1 * pp2 * qk1) + pp1 *
            pp2 * qk1 * qk2 - p1k1 * p2k2 * pp1 * qp - p2k1 * p2k2 * pp1 * qp +
            2 * p1k1 * p1k2 * pp2 * qp + p1k2 * p2k1 * pp2 * qp - p1k1 * pp2 *
            qk2 * qp - p2k1 * p2k2 * pp1 * qp1 - p2k2 * pk1 * pp1 * qp1 - 2 *
            p1k1 * pk2 * pp2 * qp1 - p2k1 * pk2 * pp2 * qp1 + k1k2 * pp1 *
            pp2 * qp1 + p1k1 * pp2 * qk2 * qp1 + 2 * p2k1 * pp2 * qk2 * qp1 +
            p1p2 * (-(pk2 * pp1 * qk1) + pp1 * qk1 * qk2 - p1k2 * (p2k1 + 2 *
            pk1) * qp + k1k2 * pp1 * qp + 2 * p2k1 * qk2 * qp + pk1 * qk2 *
            qp + (p2k1 + 2 * pk1) * pk2 * qp1 - pk1 * qk2 * qp1) + pp1 *
            (p1k2 * (p2k1 + pk1) + (p1k1 + p2k1) * pk2 - (p1k1 + 2 * p2k1 +
            pk1) * qk2) * qp2 + m2 * m2 * (-2 * p2k2 * qk1 + 2 * k1k2 * qp2) +
            m2 * (pk2 * pp2 * qk1 + p1p2 * qk1 * qk2 + pp2 * qk1 * qk2 - k1k2 *
            pp2 * qp - k1k2 * p1p2 * qp1 + p2k2 * (-2 * pp1 * qk1 + pk1 * qp +
            p1k1 * qp1 - p2k1 * (qp + qp1)) + (p2k1 * pk2 - pk1 * pk2 + 2 *
            k1k2 * pp1 - (p1k1 + 2 * p2k1 + pk1) * qk2) * qp2 + p1k2 * (p1p2 *
            qk1 + (-p1k1 + p2k1) * qp2))) + D1 * (m2 * m2 * ((-p1k2 - 2 *
            p2k2 + pk2) * qk1 + k1k2 * (-qp + qp1 + 2 * qp2)) + m2 * (-2 *
            p2k2 * pp1 * qk1 + pk2 * pp1 * qk1 + pk2 * pp2 * qk1 + 2 * pp2 *
            qk1 * qk2 + p1k1 * p2k2 * qp + p2k2 * pk1 * qp - k1k2 * pp1 * qp -
            k1k2 * pp2 * qp + 2 * p1k1 * qk2 * qp + 4 * p2k1 * qk2 * qp + 2 *
            pk1 * qk2 * qp + p1k1 * p2k2 * qp1 - 2 * p2k1 * p2k2 * qp1 - p2k2 *
            pk1 * qp1 + p1k1 * pk2 * qp1 + 4 * p2k1 * pk2 * qp1 + pk1 * pk2 *
            qp1 + k1k2 * pp1 * qp1 + k1k2 * pp2 * qp1 - 2 * p1k1 * qk2 * qp1 -
            4 * p2k1 * qk2 * qp1 - 2 * pk1 * qk2 * qp1 + p1p2 * (pk2 * qk1 -
            k1k2 * (qp + qp1)) - (p1k1 * pk2 + pk1 * pk2 - 2 * k1k2 * pp1 + 2 *
            (p2k1 + pk1) * qk2) * qp2 + p1k2 * (p1p2 * qk1 - (pp1 + pp2) *
            qk1 - (p1k1 + 4 * p2k1 + pk1) * qp + (-p1k1 + 2 * p2k1 + pk1) *
            qp2)) + 2 * (p1p2 * (p2k1 + pk1) * qk2 * qp - p1k1 * pp2 * qk2 *
            qp + p1p2 * (p2k1 + pk1) * pk2 * qp1 - p1k1 * pk2 * pp2 * qp1 +
            p2k1 * pp2 * qk2 * qp1 + pp1 * pp2 * (qk1 * qk2 + k1k2 * qp1) +
            p1k2 * (-(pp1 * pp2 * qk1) - p1p2 * (p2k1 + pk1) * qp + p1k1 *
            pp2 * qp + (p2k1 + pk1) * pp1 * qp2) - (p2k1 + pk1) * pp1 * (p2k2 *
            qp1 + qk2 * qp2))))) - 10 * (2 * C3 * C3 * D2 * D2 * p2k1 * (m2 *
            m2 * qk2 + pp1 * qk2 * qp - p1k2 * pp1 * qp1 + pp1 * qk2 * qp1 +
            p1k2 * qp * qp1 - 2 * qk2 * qp * qp1 - p1k2 * qps + pp1 * (-p1k2 +
            qk2) * u2 - pk2 * (-(qp * qp1) + qp12 + pp1 * (qp + u2)) + m2 *
            (qk2 * (pp1 + qp + qp1 + u2) - pk2 * (2 * qp + qp1 + u2) - p1k2 *
            (qp + 2 * qp1 + u2))) + 2 * C2 * C2 * D1 * D1 * pk1 * (m2 * m2 *
            qk2 + p1p2 * qk2 * qp1 - p2k2 * qp12 - p1p2 * p2k2 * qp2 + p1p2 *
            qk2 * qp2 + p2k2 * qp1 * qp2 - 2 * qk2 * qp1 * qp2 + p1p2 *
            (-p2k2 + qk2) * u2 - p1k2 * (-(qp1 * qp2) + qp22 + p1p2 * (qp1 +
            u2)) + m2 * (qk2 * (p1p2 + qp1 + qp2 + u2) - p1k2 * (2 * qp1 +
            qp2 + u2) - p2k2 * (qp1 + 2 * qp2 + u2))) + C2 * C3 * D1 * D2 *
            (2 * qp1 * (-(p1p2 * pk1 * qk2) - p2k1 * pp1 * qk2 + p1k1 * pp2 *
            qk2 - pp2 * qk1 * qk2 + p2k1 * qk2 * qp + p2k2 * pk1 * qp1 + p2k1 *
            pk2 * qp1 - k1k2 * pp2 * qp1 + pk1 * qk2 * qp2 + p1k2 * (p1p2 *
            pk1 + p2k1 * pp1 - p1k1 * pp2 + pp2 * qk1 - p2k1 * qp - pk1 *
            qp2)) + (p1p2 * pk1 + p2k1 * pp1 - p1k1 * pp2) * (2 * p1k2 - qk2) *
            u2 + m2 * m2 * (qk1 * (2 * p1k2 + p2k2 + pk2 - 2 * qk2) - (p1k1 +
            p2k1 + pk1) * qk2 + k1k2 * (qp + 2 * qp1 + qp2 + 2 * u2)) + m2 *
            (p1p2 * pk2 * qk1 + p2k2 * pp1 * qk1 - p1p2 * pk1 * qk2 - p2k1 *
            pp1 * qk2 + p1k1 * pp2 * qk2 - 2 * p1p2 * qk1 * qk2 - 2 * pp1 *
            qk1 * qk2 - 2 * pp2 * qk1 * qk2 + k1k2 * p1p2 * qp - p1k1 * p2k2 *
            qp + p2k2 * qk1 * qp + p1k1 * qk2 * qp + p2k1 * qk2 * qp + k1k2 *
            p1p2 * qp1 - p1k1 * p2k2 * qp1 - p1k1 * pk2 * qp1 + k1k2 * pp1 *
            qp1 + p2k2 * qk1 * qp1 + pk2 * qk1 * qp1 - p2k1 * qk2 * qp1 - pk1 *
            qk2 * qp1 + 2 * qk1 * qk2 * qp1 - 2 * k1k2 * qp * qp1 - p1k1 *
            pk2 * qp2 + k1k2 * pp1 * qp2 + pk2 * qk1 * qp2 + p1k1 * qk2 * qp2 +
            pk1 * qk2 * qp2 - 2 * k1k2 * qp * qp2 - 2 * k1k2 * qp1 * qp2 -
            (-2 * k1k2 * (p1p2 + pp1 + pp2) + pk1 * (p2k2 + qk2) + p2k1 *
            (pk2 + qk2) + p1k1 * (p2k2 + pk2 + qk2)) * u2 + p1k2 * (-(p1k1 *
            (qp + qp2)) + qk1 * (p1p2 + pp1 + qp + qp2) + (p2k1 + pk1) * (2 *
            qp1 + u2)))))) / 20; // clang-format on
}

} // namespace MACE::inline Simulation::inline Physics::inline DecayChannel
