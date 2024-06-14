#pragma once

#include "MACE/Extension/Geant4X/DecayChannel/AsMuoniumDecayChannel.h++"
#include "MACE/Extension/Geant4X/DecayChannel/MuonInternalPairProductionDecayChannel.h++"

namespace MACE::inline Extension::Geant4X::inline DecayChannel {

using MuoniumInternalPairProductionDecayChannel = Geant4X::AsMuoniumDecayChannel<MuonInternalPairProductionDecayChannel,
                                                                                 "MuoniumIPPDecay">;

} // namespace MACE::inline Extension::Geant4X::inline DecayChannel
