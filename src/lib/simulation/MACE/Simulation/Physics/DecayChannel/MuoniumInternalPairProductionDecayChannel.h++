#pragma once

#include "MACE/Simulation/Physics/DecayChannel/MuonInternalPairProductionDecayChannel.h++"
#include "MACE/Simulation/Physics/DecayChannel/WrapAsMuoniumDecayChannel.h++"

namespace MACE::inline Simulation::inline Physics::inline DecayChannel {

using MuoniumInternalPairProductionDecayChannel = WrapAsMuoniumDecayChannel<MuonInternalPairProductionDecayChannel, "MuoniumIPPDecay">;

} // namespace MACE::inline Simulation::inline Physics::inline DecayChannel
