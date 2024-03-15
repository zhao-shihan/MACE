#pragma once

#include "MACE/Simulation/Physics/DecayChannel/MuonInternalPairProductionDecayChannel.h++"
#include "MACE/Simulation/Physics/DecayChannel/WrapAsMuoniumDecayChannel.h++"

namespace MACE::inline Simulation::inline Physics::inline DecayChannel {

class MuoniumInternalPairProductionDecayChannel : public WrapAsMuoniumDecayChannel<MuonInternalPairProductionDecayChannel, "MuoniumIPPDecay"> {
public:
    using WrapAsMuoniumDecayChannel::WrapAsMuoniumDecayChannel;

    virtual auto MACESpecificCutApplicable() const -> bool override { return GetParentName() == "muonium"; }
};

} // namespace MACE::inline Simulation::inline Physics::inline DecayChannel
