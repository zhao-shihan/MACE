#pragma once

#include "MACE/Simulation/Physics/DecayChannel/MuoniumDecayChannelWrapper.h++"

#include "G4MuonDecayChannel.hh"

namespace MACE::inline Simulation::inline Physics::inline DecayChannel {

using MuoniumDecayChannel = MuoniumDecayChannelWrapper<G4MuonDecayChannel, "MuoniumDecay">;

} // namespace MACE::inline Simulation::inline Physics::inline DecayChannel
