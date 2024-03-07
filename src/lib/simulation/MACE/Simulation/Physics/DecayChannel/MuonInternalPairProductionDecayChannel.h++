#pragma once

#include "MACE/Extension/CLHEPX/RAMBO.h++"
#include "MACE/Math/Clamp.h++"
#include "MACE/Math/Random/Generator/Xoshiro256Plus.h++"
#include "MACE/Simulation/Physics/DecayChannel/MuonInternalPairProductionDecayChannelMessenger.h++"

#include "G4VDecayChannel.hh"

#include <algorithm>
#include <array>

namespace MACE::inline Simulation::inline Physics::inline DecayChannel {

class MuonInternalPairProductionDecayChannel : public G4VDecayChannel {
public:
    MuonInternalPairProductionDecayChannel(const G4String& parentName, G4double br, G4int verbose = 1);

    auto MetropolisDelta(double delta) -> void { fMetropolisDelta = Math::Clamp<"()">(delta, 0., 0.5); }
    auto MetropolisDiscard(int n) -> void { fMetropolisDiscard = std::max(0, n); }

    auto ApplyMACESpecificPxyCut(bool apply) -> void;

    auto DecayIt(G4double) -> G4DecayProducts* override;

private:
    virtual auto MACESpecificCutApplicable() const -> bool { return GetParentName() == "mu+"; }

    auto UpdateState(double delta) -> void;
    auto PassCut(const CLHEPX::RAMBO<5>::Event& event) const -> bool;

    static auto WeightedM2(const CLHEPX::RAMBO<5>::Event& event) -> double;

private:
    double fMetropolisDelta;
    int fMetropolisDiscard;

    bool fApplyMACESpecificPxyCut;
    bool fThermalized;

    CLHEPX::RAMBO<5> fRAMBO;
    std::array<double, 5 * 4> fRawState;
    CLHEPX::RAMBO<5>::Event fEvent;
    double fWeightedM2;

    Math::Random::Xoshiro256Plus fXoshiro256Plus;
    unsigned char fReseedCounter;

    MuonInternalPairProductionDecayChannelMessenger::Register<MuonInternalPairProductionDecayChannel> fMessengerRegister;
};

} // namespace MACE::inline Simulation::inline Physics::inline DecayChannel
