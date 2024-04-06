#pragma once

#include "MACE/Extension/Geant4X/WrapAsMuoniumDecayChannel.h++"

#include "G4MuonDecayChannelWithSpin.hh"

namespace MACE::inline Extension::Geant4X {

using MuoniumDecayChannelWithSpin = WrapAsMuoniumDecayChannel<G4MuonDecayChannelWithSpin,
                                                              "MuoniumDecayWithSpin">;

} // namespace MACE::inline Extension::Geant4X
