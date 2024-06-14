#pragma once

#include "MACE/Extension/Geant4X/DecayChannel/AsMuoniumDecayChannel.h++"

#include "G4MuonDecayChannel.hh"

namespace MACE::inline Extension::Geant4X::inline DecayChannel {

using MuoniumDecayChannel = AsMuoniumDecayChannel<G4MuonDecayChannel,
                                                  "MuoniumDecay">;

} // namespace MACE::inline Extension::Geant4X::inline DecayChannel
