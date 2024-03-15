#pragma once

#include "MACE/Simulation/Physics/DecayChannel/WrapAsMuoniumDecayChannel.h++"

#include "G4MuonDecayChannel.hh"

namespace MACE::inline Simulation::inline Physics::inline DecayChannel {

using MuoniumDecayChannel = WrapAsMuoniumDecayChannel<G4MuonDecayChannel, "MuoniumDecay">;

} // namespace MACE::inline Simulation::inline Physics::inline DecayChannel
