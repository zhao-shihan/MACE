#pragma once

#include "MACE/Math/RAMBO.h++"
#include "MACE/Simulation/Physics/DecayChannel/MuonInternalPairProductionDecayChannelMessenger.h++"

#include "G4VDecayChannel.hh"

#include <array>

namespace MACE::inline Simulation::inline Physics::inline DecayChannel {

class MuonInternalPairProductionDecayChannel final : public G4VDecayChannel {
public:
    MuonInternalPairProductionDecayChannel(const G4String& parentName, G4double br, G4int verbose = 1);

    auto MetropolisDelta(double delta) -> void { fMetropolisDelta = delta; }
    auto MetropolisDiscard(double n) -> void { fMetropolisDiscard = n; }
    auto MetropolisWarmupCycle(int n) -> void { fMetropolisWarmupCycle = n; }
    auto SameChargedFinalStateEnergyCut(double eUp) -> void;

    auto DecayIt(G4double) -> G4DecayProducts* override;

private:
    auto UpdateState(CLHEP::HepRandomEngine& rng) -> void;
    auto Thermalize() -> void;

    auto Cut(const Math::RAMBO<5>::Event& event) const -> bool;

    static auto WeightedM2(const Math::RAMBO<5>::Event& event) -> double;

private:
    double fMetropolisDelta;
    int fMetropolisDiscard;
    int fMetropolisWarmupCycle;
    double fSameChargedFinalStateEnergyCut;

    Math::RAMBO<5> fRAMBO;
    std::array<double, 5 * 4> fRawState;
    Math::RAMBO<5>::Event fEvent;
    double fWeightedM2;

    MuonInternalPairProductionDecayChannelMessenger::Register<MuonInternalPairProductionDecayChannel> fMessengerRegister;
};

} // namespace MACE::inline Simulation::inline Physics::inline DecayChannel
