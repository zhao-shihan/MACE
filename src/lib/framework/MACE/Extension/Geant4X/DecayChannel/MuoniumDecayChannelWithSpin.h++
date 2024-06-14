#pragma once

#include "MACE/Extension/Geant4X/DecayChannel/AsMuoniumDecayChannel.h++"

#include "G4MuonDecayChannelWithSpin.hh"

namespace MACE::inline Extension::Geant4X::inline DecayChannel {

using MuoniumDecayChannelWithSpin = AsMuoniumDecayChannel<G4MuonDecayChannelWithSpin,
                                                          "MuoniumDecayWithSpin">;

} // namespace MACE::inline Extension::Geant4X::inline DecayChannel
