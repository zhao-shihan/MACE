#pragma once

#include "MACE/Extension/Geant4X/WrapAsMuoniumDecayChannel.h++"
#include "MACE/Simulation/Physics/DecayChannel/MuonInternalPairProductionDecayChannel.h++"

namespace MACE::inline Simulation::inline Physics::inline DecayChannel {

class MuoniumInternalPairProductionDecayChannel : public Geant4X::WrapAsMuoniumDecayChannel<MuonInternalPairProductionDecayChannel,
                                                                                            "MuoniumIPPDecay"> {
public:
    using WrapAsMuoniumDecayChannel::WrapAsMuoniumDecayChannel;

    virtual auto MACESpecificCutApplicable() const -> bool override { return GetParentName() == "muonium"; }
};

} // namespace MACE::inline Simulation::inline Physics::inline DecayChannel
