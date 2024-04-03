#pragma once

#include "MACE/Simulation/Physics/DecayChannel/WrapAsMuoniumDecayChannel.h++"

#include "G4MuonDecayChannelWithSpin.hh"

namespace MACE::inline Simulation::inline Physics::inline DecayChannel {

using MuoniumDecayChannelWithSpin = WrapAsMuoniumDecayChannel<G4MuonDecayChannelWithSpin, "MuoniumDecayWithSpin">;

} // namespace MACE::inline Simulation::inline Physics::inline DecayChannel
