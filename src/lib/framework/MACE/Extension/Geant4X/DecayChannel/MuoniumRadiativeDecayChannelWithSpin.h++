#pragma once

#include "MACE/Extension/Geant4X/DecayChannel/AsMuoniumDecayChannel.h++"

#include "G4MuonRadiativeDecayChannelWithSpin.hh"

namespace MACE::inline Extension::Geant4X::inline DecayChannel {

using MuoniumRadiativeDecayChannelWithSpin = AsMuoniumDecayChannel<G4MuonRadiativeDecayChannelWithSpin,
                                                                   "MuoniumRadiativeDecayChannelWithSpin">;

} // namespace MACE::inline Extension::Geant4X::inline DecayChannel
