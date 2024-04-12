#pragma once

#include "MACE/Extension/Geant4X/WrapAsMuoniumDecayChannel.h++"

#include "G4MuonDecayChannel.hh"

namespace MACE::inline Extension::Geant4X {

using MuoniumDecayChannel = WrapAsMuoniumDecayChannel<G4MuonDecayChannel,
                                                      "MuoniumDecay">;

} // namespace MACE::inline Extension::Geant4X
