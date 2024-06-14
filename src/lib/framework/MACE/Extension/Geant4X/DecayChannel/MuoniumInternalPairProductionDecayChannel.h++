#pragma once

#include "MACE/Extension/Geant4X/DecayChannel/AsMuoniumDecayChannel.h++"
#include "MACE/Extension/Geant4X/DecayChannel/MuonInternalPairProductionDecayChannel.h++"

namespace MACE::inline Extension::Geant4X::inline DecayChannel {

class MuoniumInternalPairProductionDecayChannel : public Geant4X::AsMuoniumDecayChannel<MuonInternalPairProductionDecayChannel,
                                                                                        "MuoniumIPPDecay"> {
public:
    using AsMuoniumDecayChannel::AsMuoniumDecayChannel;

    virtual auto PassCutApplicable() const -> bool override { return GetParentName() == "muonium"; }
};

} // namespace MACE::inline Extension::Geant4X::inline DecayChannel
